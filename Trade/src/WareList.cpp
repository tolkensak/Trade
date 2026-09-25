
#include "stdafx.h"
#include "App.h"
#include "WareList.h"
#include "Convertion.h"


BEGIN_MESSAGE_MAP(WareList, CListCtrl)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


WareList::WareList()
{
	int i=0;
	m_arrColumn.Add(Column(IDS_COL_NAME, Column::typeText, 110, i++));
	m_arrColumn.Add(Column(IDS_COL_CAT, Column::typeText, 110, i++));
	m_arrColumn.Add(Column(IDS_COL_FIRM, Column::typeText, 110, i++));
}

WareList::~WareList()
{
}

//BOOL WareList::PreCreateWindow(CREATESTRUCT& cs)
//{
//	cs.style&=~LVS_NOCOLUMNHEADER;
//	cs.style|=LVS_SINGLESEL|LVS_REPORT|LVS_SHOWSELALWAYS;
//	return CListCtrl::PreCreateWindow(cs);
//}

void WareList::PreSubclassWindow()
{
	CListCtrl::PreSubclassWindow();

	DWORD dwStyle=GetWindowLongPtr(m_hWnd, GWL_STYLE);
	dwStyle&=~LVS_NOCOLUMNHEADER;
	SetWindowLongPtr(m_hWnd, GWL_STYLE, dwStyle|LVS_SINGLESEL|LVS_REPORT|LVS_SHOWSELALWAYS);

	SetExtendedStyle(GetExtendedStyle()|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	LayColumn();
}

//int WareList::OnCreate(LPCREATESTRUCT pcs)
//{
//	if(CListCtrl::OnCreate(pcs)==-1)
//		return -1;
//
//	SetExtendedStyle(GetExtendedStyle()|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
//	LayColumn();
//
//	return 0;
//}

void WareList::OnSetFocus(CWnd* pOldWnd)
{
	if(GetItemCount()==0)
		GetParent()->GetNextDlgTabItem(this, TRUE)->SetFocus();
	else
		CListCtrl::OnSetFocus(pOldWnd);
}

void WareList::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if(nChar==VK_UP)
	{
		if((GetItemState(0, LVIS_SELECTED|LVIS_FOCUSED)&(LVIS_SELECTED|LVIS_FOCUSED))==(LVIS_SELECTED|LVIS_FOCUSED))
			GetParent()->GetNextDlgTabItem(this, TRUE)->SetFocus();
	}

	CListCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL WareList::LayColumn()
{
	int i;
	CHeaderCtrl* pHeader=GetHeaderCtrl();

	for(i=pHeader->GetItemCount()-1; i>=0; i--)
		DeleteColumn(i);

	CString str;
	const Column* pCol;

	HDITEM hdi;
	hdi.mask=HDI_LPARAM;//|HDI_TEXT|HDI_WIDTH|HDI_FORMAT;

	int n=m_arrColumn.GetCount();

	for(i=0; i<n; i++)
	{
		pCol=&m_arrColumn[i];
		str.LoadString(pCol->GetStrID());

		InsertColumn(i, str, pCol->GetFormat(), pCol->GetWidth(), pCol->GetSubItem());

		//hdi.pszText=str.GetBuffer();
		//hdi.cxy=pCol->GetWidth();
		//hdi.fmt=pCol->GetFormat();
		hdi.lParam=pCol->GetType();
		pHeader->SetItem(i, &hdi);
		//str.ReleaseBuffer();
	}

	return TRUE;
}

void WareList::Reload(const CString& strPrefix)
{
	DeleteAllItems();

	if(strPrefix.IsEmpty())
		return;

	StringA stra;

	HKL hkl=GetKeyboardLayout(GetCurrentThreadId());
	if(LOWORD(hkl)==1033)
	{
		CString cstr(strPrefix);
		ConvertLatToCyr(cstr);
		stra.Format("call sp_ware_search2('%s%%', '%s%%')", WcharToUtf8(strPrefix), WcharToUtf8(cstr));
	}
	else
		stra.Format("call sp_ware_search('%s%%')", WcharToUtf8(strPrefix));

	MySQLResPtr pRes=theApp.Query(stra, this, TRUE);
	if(!pRes)
		return;

	CHeaderCtrl* pHeader=GetHeaderCtrl();
	HDITEM hdi;
	hdi.mask=HDI_LPARAM;

	TCHAR pch[TOL_MAXSTR];
	LVITEM lvi;
	lvi.mask=LVIF_TEXT;
	lvi.pszText=pch;
	lvi.iItem=0;

	int i=pRes->NumFields()-1;
	int nCol=pHeader->GetItemCount();
	if(nCol>i)
		nCol=i;

	int j;
	PULONG len;
	MYSQL_ROW row;

	while(row=pRes->FetchRow())
	{
		len=pRes->FetchLengths();

		for(lvi.iSubItem=0, j=1; lvi.iSubItem<nCol; lvi.iSubItem++, j++)
		{
			if(!row[j])
				continue;

			pHeader->GetItem(lvi.iSubItem, &hdi);

			Utf8ToWchar(row[j], len[j], pch);

			if(lvi.iSubItem)
				SetItem(&lvi);
			else
			{
				lvi.mask|=LVIF_PARAM;
				lvi.lParam=atol(row[0]);
				i=InsertItem(&lvi);
				lvi.mask&=~LVIF_PARAM;

				if(i==-1)
					break;

				lvi.iItem=i;
			}
		}

		lvi.iItem++;
	}

	SetItemState(0, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
}
