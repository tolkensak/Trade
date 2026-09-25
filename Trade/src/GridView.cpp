
#include "stdafx.h"
#include "GridView.h"
#include "resource.h"

#define GV_FIRST_COLUMN_ID 35100
#define GV_LAST_COLUMN_ID 35200


BEGIN_MESSAGE_MAP(GridView, CListView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_CONTEXTMENU()
	ON_NOTIFY(HDN_ENDDRAG, 0, &GridView::OnHdnEndDrag)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &GridView::OnNMDblclk)
	//ON_WM_LBUTTONDBLCLK()
	ON_MESSAGE(UM_UPDATE_UI, &GridView::OnUmUpdateUI)
	ON_COMMAND_RANGE(GV_FIRST_COLUMN_ID, GV_LAST_COLUMN_ID, &GridView::OnColumn)
END_MESSAGE_MAP()


GridView::GridView(UINT uUniqueID)
	: m_uUniqueID(uUniqueID)
	, m_strEmptyMessage(_T("Empty"))
{
	SetEmptyMessage(IDS_EMPTY_MESSAGE);
}

GridView::~GridView()
{
}

BOOL GridView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style&=~LVS_TYPEMASK;
	cs.style|=LVS_REPORT|LVS_SHOWSELALWAYS;
	return CListView::PreCreateWindow(cs);
}

int GridView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if(CListView::OnCreate(lpCreateStruct)==-1)
		return -1;

	GetListCtrl().SetExtendedStyle(LVS_EX_FULLROWSELECT
#if _WIN32_WINNT>=0x501
		|LVS_EX_DOUBLEBUFFER
#endif
		|LVS_EX_GRIDLINES);

	if(!LayColumn())
		return -1;

	RestoreColumn();
	return 0;
}

void GridView::OnDestroy()
{
	StoreColumn();
	CListView::OnDestroy();
}

BOOL GridView::ContextMenuClient(HMENU hMenu, UINT* puFlags, int iItem)
{
	return FALSE;
}

void GridView::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	CListCtrl& lc=GetListCtrl();
	CRect rc;
	int nItem=-1;

	if(point.x==-1 && point.y==-1)
	{
		int nItem=lc.GetNextItem(-1, LVNI_SELECTED);
		if(nItem<0)
		{
			lc.GetHeaderCtrl()->GetWindowRect(&rc);
			point.x=0;
			point.y=rc.Height();
		}
		else
		{
			lc.GetItemRect(nItem, &rc, LVIR_ICON);
			point.x=(rc.right+rc.left)/2;
			point.y=(rc.bottom+rc.top)/2;
		}
	}
	else
	{
		ScreenToClient(&point);
		lc.GetHeaderCtrl()->GetWindowRect(&rc);

		if(point.y<rc.Height())
		{
			ContextMenuHeader(point);
			return;
		}
		else
		{
			LVHITTESTINFO lvhti;
			lvhti.pt=point;
			lvhti.flags=LVHT_ONITEM;
			nItem=lc.HitTest(&lvhti);
		}
	}

	HMENU hMenu=CreatePopupMenu();
	UINT uFlags=TPM_LEFTALIGN|TPM_TOPALIGN;

	if(!ContextMenuClient(hMenu, &uFlags, nItem))
	{
		DestroyMenu(hMenu);
		return;
	}

	TSDIMVMainWndLang* pMainWnd=(TSDIMVMainWndLang*)AfxGetMainWnd();
	if(pMainWnd->IsMenuStyle())
		MenuOD_SetOwnerDraw(hMenu, TRUE, FALSE);

	pMainWnd->SetForegroundWindow();

	ClientToScreen(&point);
	TrackPopupMenuEx(hMenu, uFlags, point.x, point.y, pMainWnd->m_hWnd, NULL);

	DestroyMenu(hMenu);
	pMainWnd->PostMessage(WM_NULL, 0, 0);
}

void GridView::DblClkItem(int nItem)
{
}

void GridView::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pnmia=reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	DblClkItem(pnmia->iItem);
	*pResult=0;
}

//void GridView::OnLButtonDblClk(UINT nFlags, CPoint point)
//{
//	CListView::OnLButtonDblClk(nFlags, point);
//
//	LVHITTESTINFO hti;
//	hti.pt=point;
//	hti.objs=LVHT_ONITEM;
//	GetListCtrl().HitTest(&hti);
//	if(hti.iItem!=-1)
//		DblClkItem(hti.iItem);
//}

BOOL GridView::LayColumn()
{
	int i;
	CListCtrl& lc=GetListCtrl();
	CHeaderCtrl* pHeader=lc.GetHeaderCtrl();

	for(i=pHeader->GetItemCount()-1; i>=0; i--)
		lc.DeleteColumn(i);

	CString str;
	const Column* pCol;

	HDITEM hdi;
	hdi.mask=HDI_LPARAM;//|HDI_TEXT|HDI_WIDTH|HDI_FORMAT;

	int n=m_arrColumn.GetCount();

	for(i=0; i<n; i++)
	{
		pCol=&m_arrColumn[i];
		str.LoadString(pCol->GetStrID());

		lc.InsertColumn(i, str, pCol->GetFormat(), pCol->GetWidth(), pCol->GetSubItem());

		//hdi.pszText=str.GetBuffer();
		//hdi.cxy=pCol->GetWidth();
		//hdi.fmt=pCol->GetFormat();
		hdi.lParam=pCol->GetType();
		pHeader->SetItem(i, &hdi);
		//str.ReleaseBuffer();
	}

	return TRUE;
}

void GridView::RestoreColumn()
{
	if(GetUniqueID()==0)
		return;

	CListCtrl& lc=GetListCtrl();
	int n=lc.GetHeaderCtrl()->GetItemCount();
	if(n==0)
		return;

	CString strKey;
	CWinApp* pApp=AfxGetApp();

	strKey.Format(_T("GridView\\%u"), GetUniqueID());
	if(n!=pApp->GetProfileInt(strKey, _T("ColNum"), 0))
		return;

	UINT sz;
	int* pn;

	if(pApp->GetProfileBinary(strKey, _T("ColWidth"), (LPBYTE*)&pn, &sz))
	{
		LVCOLUMN lvc;
		lvc.mask=LVCF_WIDTH;

		for(int i=0; i<n; i++)
		{
			lvc.cx=pn[i];
			lc.SetColumn(i, &lvc);
		}
	}

	delete[] pn;

	//if(pApp->GetProfileBinary(strKey, _T("ColOrder"), (LPBYTE*)&pn, &sz))
	//	lc.SetColumnOrderArray(n, pn);

	//delete[] pn;
}

void GridView::StoreColumn()
{
	if(GetUniqueID()==0)
		return;

	CListCtrl& lc=GetListCtrl();
	int n=lc.GetHeaderCtrl()->GetItemCount();

	CString strKey;
	CWinApp* pApp=AfxGetApp();
	strKey.Format(_T("GridView\\%u"), GetUniqueID());
	pApp->WriteProfileInt(strKey, _T("ColNum"), n);

	if(n==0)
		return;

	int* pn=new int[n];
	UINT sz=n*sizeof(int);

	LVCOLUMN lvc;
	lvc.mask=LVCF_WIDTH;

	for(int i=0; i<n; i++)
	{
		lc.GetColumn(i, &lvc);
		pn[i]=lvc.cx;
	}

	pApp->WriteProfileBinary(strKey, _T("ColWidth"), (LPBYTE)pn, sz);

	//lc.GetColumnOrderArray(pn, n);
	//pApp->WriteProfileBinary(strKey, _T("ColOrder"), (LPBYTE)pn, sz);

	delete[] pn;
}

LRESULT GridView::OnUmUpdateUI(WPARAM wp, LPARAM lp)
{
	if(wp!=UPDATE_UI_LANG)
		return 0;

	SetEmptyMessage(IDS_EMPTY_MESSAGE);

	LVCOLUMN lvc;
	TCHAR pch[256];
	CListCtrl& lc=GetListCtrl();
	HINSTANCE hInst=AfxGetResourceHandle();

	lvc.mask=LVCF_TEXT;
	lvc.pszText=pch;

	for(int i=m_arrColumn.GetCount()-1; i>=0; i--)
	{
		LoadString(hInst, m_arrColumn[i].GetStrID(), pch, 256);
		lc.SetColumn(i, &lvc);
	}

	return 0;
}

void GridView::OnHdnEndDrag(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr=reinterpret_cast<LPNMHEADER>(pNMHDR);
	if(phdr->pitem->mask&HDI_ORDER)
	{
		// Correct iOrder so it is just after the last hidden column
		CListCtrl& lc=GetListCtrl();
		int i, n=lc.GetHeaderCtrl()->GetItemCount();
		int* pn=new int[n];

		lc.GetColumnOrderArray(pn, n);

		for(i=0; i<n; i++)
		{
			phdr->pitem->iOrder=max(phdr->pitem->iOrder, i);
			Invalidate();
			break;
		}

		delete[] pn;
	}

	*pResult=0;
}

void GridView::ContextMenuHeader(CPoint pt)
{
	CListCtrl& lc=GetListCtrl();
	int n=lc.GetHeaderCtrl()->GetItemCount();
	int *pn=new int[n];

	lc.GetColumnOrderArray(pn, n);

	TCHAR pc[80];
	LVCOLUMN lvc;
	lvc.mask=LVCF_TEXT|LVCF_WIDTH;
	lvc.cchTextMax=80;
	lvc.pszText=pc;

	int i, j;
	HMENU hMenu=CreatePopupMenu();

	for(i=0; i<n; i++)
	{
		j=pn[i];
		lc.GetColumn(j, &lvc);
		AppendMenu(hMenu, (lvc.cx?MF_CHECKED:0)|MF_STRING, (GV_FIRST_COLUMN_ID)+j, pc);
	}

	TSDIMVMainWndLang* pMainWnd=(TSDIMVMainWndLang*)AfxGetMainWnd();
	if(pMainWnd->IsMenuStyle())
		MenuOD_SetOwnerDraw(hMenu, TRUE, FALSE);

	pMainWnd->SetForegroundWindow();

	ClientToScreen(&pt);
	TrackPopupMenuEx(hMenu, TPM_LEFTALIGN|TPM_TOPALIGN, pt.x, pt.y, pMainWnd->m_hWnd, NULL);
	DestroyMenu(hMenu);
	pMainWnd->PostMessage(WM_NULL, 0, 0);

	//CListCtrl& lc=GetListCtrl();
	//int n=lc.GetHeaderCtrl()->GetItemCount();
	//int *pn=new int[n];

	//lc.GetColumnOrderArray(pn, n);

	//TCHAR pc[80];
	//LVCOLUMN lvc;
	//lvc.mask=LVCF_TEXT|LVCF_WIDTH;
	//lvc.cchTextMax=80;
	//lvc.pszText=pc;

	//int i, j;
	//HMENU hMenu=CreatePopupMenu();

	//for(i=0; i<n; i++)
	//{
	//	j=pn[i];
	//	lc.GetColumn(j, &lvc);
	//	AppendMenu(hMenu, (lvc.cx?MF_CHECKED:0)|MF_STRING|(j==0?MF_GRAYED:0), j+1, pc);
	//}

	//CWnd* pMainWnd=AfxGetMainWnd();
	//pMainWnd->SetForegroundWindow();

	//ClientToScreen(&pt);
	//j=TrackPopupMenuEx(hMenu, TPM_RETURNCMD|TPM_LEFTALIGN|TPM_TOPALIGN, pt.x, pt.y, pMainWnd->m_hWnd, NULL);

	//DestroyMenu(hMenu);
	//pMainWnd->PostMessage(WM_NULL, 0, 0);

	//if(j--)
	//{
	//	int cx=lc.GetColumnWidth(j);
	//	cx=cx?0:LVSCW_AUTOSIZE;
	//	lc.SetColumnWidth(j, cx);
	//}

	delete[] pn;
}

void GridView::OnColumn(UINT uCmdID)
{
	if(uCmdID<GV_FIRST_COLUMN_ID)
		return;

	CListCtrl& lc=GetListCtrl();
	int i=uCmdID-GV_FIRST_COLUMN_ID;

	if(i>=lc.GetHeaderCtrl()->GetItemCount())
		return;

	int cx=lc.GetColumnWidth(i);
	if(cx==0)
	{
		cx=m_arrColumn[i].GetWidth();
	}
	else
	{
		m_arrColumn[i].SetWidth(cx);
		cx=0;
	}

	lc.SetColumnWidth(i, cx);
}

void GridView::SetEmptyMessage(UINT uResID)
{
	if(uResID)
		m_strEmptyMessage.LoadString(uResID);
	else
		m_strEmptyMessage.Empty();
}

void GridView::SetEmptyMessage(LPCTSTR pc)
{
	if(pc)
		m_strEmptyMessage=pc;
	else
		m_strEmptyMessage.Empty();
}

void GridView::OnPaint()
{
	Default();

	CListCtrl& lc=GetListCtrl();
	if(lc.GetItemCount() || m_strEmptyMessage.IsEmpty())
		return;

#ifdef SPECCLASSNAME
	if(strcmp(GetParent()->GetRuntimeClass()->m_lpszClassName, SPECCLASSNAME))
		return;
#endif

	CRect rc;
	GetClientRect(&rc);

	CHeaderCtrl* pHeader=lc.GetHeaderCtrl();
	if(pHeader)
	{
		CRect rc2;
		pHeader->GetItemRect(0, &rc2);
		rc.top+=rc2.Height();
	}

	CDC* pDC=GetDC();
	CGdiObject* pOldFont=pDC->SelectStockObject(DEFAULT_GUI_FONT);
	int nOldBkMode=pDC->SetBkMode(TRANSPARENT);

	pDC->FillSolidRect(&rc, lc.GetBkColor());
	pDC->DrawText(_T("\n")+m_strEmptyMessage, -1, rc, DT_CENTER|DT_WORDBREAK|DT_NOPREFIX);

	pDC->SetBkMode(nOldBkMode);
	pDC->SelectObject(pOldFont);
	ReleaseDC(pDC);
}
