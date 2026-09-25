
#include "stdafx.h"
#include "App.h"
#include "TableView.h"
#include "FormatStr.h"


BEGIN_MESSAGE_MAP(TableView, GridView)
	ON_MESSAGE(UM_VIEW_ACTIVATED, &TableView::OnViewActivated)
	ON_COMMAND(ID_VIEW_RELOAD, &TableView::OnViewReload)
	ON_COMMAND(ID_DATA_NEW, &TableView::OnDataNew)
	ON_COMMAND(ID_DATA_EDIT, &TableView::OnDataEdit)
	ON_COMMAND(ID_DATA_DELETE, &TableView::OnDataDelete)
	ON_UPDATE_COMMAND_UI(ID_DATA_EDIT, &TableView::OnUpdateDataEdit)
	ON_UPDATE_COMMAND_UI(ID_DATA_DELETE, &TableView::OnUpdateDataDelete)
	ON_MESSAGE(UM_UPDATE_UI, &TableView::OnUmUpdateUI)
END_MESSAGE_MAP()


TableView::TableView(UINT uUniqueID)
	: GridView(uUniqueID)
	, m_bFirstTimeActivated(TRUE)
{
}

TableView::~TableView()
{
}

BOOL TableView::ContextMenu(HMENU hMenu, UINT* puFlags, int iItem)
{
	HMENU hMenuMain=AfxGetMainWnd()->GetMenu()->GetSafeHmenu();
	if(!hMenuMain)
		return FALSE;

	Menu_CopyItem(hMenu, -1, hMenuMain, ID_DATA_NEW, TRUE);
	Menu_CopyItem(hMenu, -1, hMenuMain, ID_DATA_EDIT, TRUE);
	Menu_CopyItem(hMenu, -1, hMenuMain, ID_DATA_DELETE, TRUE);

	return TRUE;
}

LRESULT TableView::OnViewActivated(WPARAM wp, LPARAM lp)
{
	if(m_bFirstTimeActivated || wp==1)
	{
		Reload();
		m_bFirstTimeActivated=FALSE;
	}
	else if(m_rm.IsModified())
	{
		Reload();
	}
	else
	{
		SetStatusNumPaneText();
		SetStatusSumPaneText();
	}

	return 0;
}

void TableView::OnViewReload()
{
	Reload();
}

BOOL TableView::DataNew(OBJID& oid)
{
	return FALSE;
}

BOOL TableView::DataEdit(OBJID& oid)
{
	return FALSE;
}

void TableView::DblClkItem(int nItem)
{
	if(nItem==-1)
		return;

	OBJID oid=GetItemObjID(nItem);
	if(oid && DataEdit(oid))
		Reload(oid);
}

void TableView::OnDataNew()
{
	OBJID oid=0;
	if(DataNew(oid))
		Reload(oid);
}

void TableView::OnDataEdit()
{
	OBJID oid=GetFirstSelectedItemObjID();
	if(oid && DataEdit(oid))
		Reload(oid);
}

BOOL TableView::CanDataDelete(StringA& fmtQuery)
{
	OBJID oidPermit;

	switch(GetUniqueID())
	{
	case IDR_WARE:
		oidPermit=ID_PERMIT_DELETE_WARE;
		fmtQuery="delete from ware where id=%u";
		break;
	case IDR_WARE_CAT:
		oidPermit=ID_PERMIT_DELETE_WARE;
		fmtQuery="call sp_ware_cat_delete(%u)";
		break;
	case IDR_UNIT:
		oidPermit=ID_PERMIT_DELETE_UNIT;
		fmtQuery="delete from unit where id=%u";
		break;
	case IDR_UNIT_CAT:
		oidPermit=ID_PERMIT_DELETE_UNIT;
		fmtQuery="call sp_unit_cat_delete(%u)";
		break;
	case IDR_USER:
		oidPermit=ID_PERMIT_DELETE_USER;
		fmtQuery="delete from `user` where id=%u";
		break;
	case IDR_BUY:
		oidPermit=ID_PERMIT_BUY;
		fmtQuery="delete from buy_lot where id=%u";
		break;
	case IDR_SELL:
		oidPermit=ID_PERMIT_SELL;
		fmtQuery="delete from sell_lot where id=%u";
		break;
	case IDR_FIRM:
		oidPermit=ID_PERMIT_DELETE_FIRM;
		fmtQuery="call sp_firm_delete(%u)";
		break;
	case IDR_CLIENT:
		oidPermit=ID_PERMIT_DELETE_CLIENT;
		fmtQuery="delete from `client` where id=%u";
		break;
	case IDR_INDENT:
		oidPermit=ID_PERMIT_INDENT;
		fmtQuery="call sp_indent_delete(%u)";
		break;
	default:
		return FALSE;
	}

	if(!theApp.CheckPermit(oidPermit))
	{
		MsgBox(NULL, MB_ICONINFORMATION, IDS_ERR_NO_PERMIT);
		return FALSE;
	}

	return TRUE;
}

BOOL TableView::DataDelete(int* pnDelete, int nCount, PCCharA pcFormat)
{
	if(!pnDelete || !nCount || !pcFormat)
		return FALSE;

	if(MsgBox(NULL, MB_YESNO|MB_ICONQUESTION|MB_DEFBUTTON2, IDS_PROMPT_DELETE)==IDNO)
		return FALSE;

	const Connection& conn=theApp.Connect();
	if(!conn)
		return FALSE;

	StringA stra;
	BOOL bRet=FALSE;

	for(int i=0; i<nCount; i++)
	{
		stra.Format(pcFormat, GetItemObjID(pnDelete[i]));

		if(conn.RealQuery((PCCharA)stra, stra.Len())==0)
			bRet=TRUE;
		else
		{
			CString strName=GetListCtrl().GetItemText(pnDelete[i], 0);

			if(conn.Errno()==1451) // Foreign key
				MsgBox(NULL, MB_ICONINFORMATION, IDS_ERR_DELETE_FOREIGN, strName);
			else
			{
				CString strErr;
				conn.ErrorStr(strErr);
				MsgBox(NULL, MB_ICONINFORMATION, IDS_ERR_ON_DELETE, strName, strErr);
			}

			pnDelete[i]=-1;
		}
	}

	return bRet;
}

void TableView::OnDataDelete()
{
	CListCtrl& lc=GetListCtrl();
	int i=lc.GetSelectedCount();
	if(i==0)
		return;

	StringA fmtQuery;
	if(!CanDataDelete(fmtQuery))
		return;

	int* pn=new int[i];
	POSITION pos=lc.GetFirstSelectedItemPosition();
	i=0;
	while(pos)
		pn[i++]=lc.GetNextSelectedItem(pos);

	if(DataDelete(pn, i, fmtQuery))
	{
		for(i--; i>=0; i--)
			if(pn[i]!=-1)
				lc.DeleteItem(pn[i]);

		m_rm.SetModified(ReloadMgr::oprDelete);
		m_rm.UnsetModified();

		SetStatusNumPaneText();
		SetStatusSumPaneText();
	}

	delete[] pn;
}

void TableView::OnUpdateDataEdit(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetListCtrl().GetSelectedCount()==1);
}

void TableView::OnUpdateDataDelete(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetListCtrl().GetSelectedCount());
}

int TableView::GetFirstSelectedItem() const
{
	CListCtrl& lc=GetListCtrl();
	POSITION pos=lc.GetFirstSelectedItemPosition();
	return pos?lc.GetNextSelectedItem(pos):-1;
}

void TableView::Reload()
{
	static TCHAR pch[TOL_MAXSTR];

	CListCtrl& lc=GetListCtrl();
	lc.DeleteAllItems();

	if(m_straReload.IsEmpty())
		return;

	MySQLResPtr pRes=theApp.Query(m_straReload, this, TRUE);
	if(!pRes)
		return;

	CHeaderCtrl* pHeader=lc.GetHeaderCtrl();
	COleDateTime datetime;
	HDITEM hdi;
	hdi.mask=HDI_LPARAM;

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

	CString cstrYes;
	cstrYes.LoadString(IDYES);

	FormatStr fmtDT(FormatStr::typeLoad, FormatStr::partDateTime);
	FormatStr fmtD(FormatStr::typeLoad, FormatStr::partDate);
	FormatStr fmtT(FormatStr::typeLoad, FormatStr::partTime);

	while(row=pRes->FetchRow())
	{
		len=pRes->FetchLengths();

		for(lvi.iSubItem=0, j=1; lvi.iSubItem<nCol; lvi.iSubItem++, j++)
		{
			if(!row[j])
				continue;

			pHeader->GetItem(lvi.iSubItem, &hdi);

			if(hdi.lParam==Column::typeBoolean)
			{
				if(atoi(row[j]))
					lstrcpy(pch, cstrYes);
				else
					pch[0]=_T('\0');
			}
			else
			{
				Utf8ToWchar(row[j], len[j], pch);

				if(hdi.lParam==Column::typeDateTime)
				{
					datetime.ParseDateTime(pch);
					lstrcpy(pch, datetime.Format(fmtDT));
				}
				else if(hdi.lParam==Column::typeDate)
				{
					datetime.ParseDateTime(pch);
					lstrcpy(pch, datetime.Format(fmtD));
				}
				else if(hdi.lParam==Column::typeTime)
				{
					datetime.ParseDateTime(pch);
					lstrcpy(pch, datetime.Format(fmtT));
				}
			}

			if(lvi.iSubItem)
				lc.SetItem(&lvi);
			else
			{
				lvi.mask|=LVIF_PARAM;
				lvi.lParam=atol(row[0]);
				i=lc.InsertItem(&lvi);
				lvi.mask&=~LVIF_PARAM;

				if(i==-1)
					break;

				lvi.iItem=i;
			}
		}

		lvi.iItem++;
	}

	SetStatusNumPaneText();
	SetStatusSumPaneText();

	m_rm.UnsetModified();
}

int TableView::GetItemIndex(OBJID oid) const
{
	CListCtrl& lc=GetListCtrl();

	int n=lc.GetItemCount();
	for(int i=0; i<n; i++)
		if(lc.GetItemData(i)==oid)
			return i;

	return -1;
}

void TableView::Reload(OBJID oid)
{
	static TCHAR pch[TOL_MAXSTR];

	if(m_straReloadRow.IsEmpty())
		return;

	StringA stra;
	stra.Format((PCCharA)m_straReloadRow, oid);

	MySQLResPtr pRes=theApp.Query(stra, this);
	if(!pRes)
		return;

	MYSQL_ROW row=pRes->FetchRow();
	if(!row)
		return;

	CListCtrl& lc=GetListCtrl();
	CHeaderCtrl* pHeader=lc.GetHeaderCtrl();

	HDITEM hdi;
	hdi.mask=HDI_LPARAM;

	LVITEM lvi;
	lvi.mask=LVIF_TEXT;
	lvi.pszText=pch;
	lvi.iItem=GetItemIndex(oid);

	int j=pRes->NumFields()-1;
	int nCol=pHeader->GetItemCount();
	if(nCol>j)
		nCol=j;

	PULONG len=pRes->FetchLengths();

	for(lvi.iSubItem=0, j=1; lvi.iSubItem<nCol; lvi.iSubItem++, j++)
	{
		pch[0]=_T('\0');

		if(row[j])
		{
			pHeader->GetItem(lvi.iSubItem, &hdi);

			if(hdi.lParam==Column::typeBoolean)
			{
				if(atoi(row[j]))
					LoadString(AfxGetResourceHandle(), IDYES, pch, TOL_MAXSTR);
			}
			else
			{
				Utf8ToWchar(row[j], len[j], pch);

				if(hdi.lParam==Column::typeDateTime)
				{
					COleDateTime datetime;
					datetime.ParseDateTime(pch);

					FormatStr fmtDT(FormatStr::typeLoad, FormatStr::partDateTime);
					lstrcpy(pch, datetime.Format(fmtDT));
				}
				else if(hdi.lParam==Column::typeDate)
				{
					COleDateTime date;
					date.ParseDateTime(pch);

					FormatStr fmtD(FormatStr::typeLoad, FormatStr::partDate);
					lstrcpy(pch, date.Format(fmtD));
				}
				else if(hdi.lParam==Column::typeTime)
				{
					COleDateTime time;
					time.ParseDateTime(pch);

					FormatStr fmtT(FormatStr::typeLoad, FormatStr::partTime);
					lstrcpy(pch, time.Format(fmtT));
				}
			}
		}

		if(lvi.iItem==-1)
		{
			lvi.iItem=lc.GetItemCount();

			lvi.mask|=LVIF_PARAM;
			lvi.lParam=atol(row[0]);
			lvi.iItem=lc.InsertItem(&lvi);
			lvi.mask&=~LVIF_PARAM;

			if(lvi.iItem==-1)
				return;
		}
		else
			lc.SetItem(&lvi);
	}

	SetStatusNumPaneText();
	SetStatusSumPaneText();

	m_rm.UnsetModified();
}

BOOL TableView::GetSum(double& dSum) const
{
	return FALSE;
}

void TableView::SetStatusSumPaneText() const
{
	double dSum;

	if(GetSum(dSum))
		SetStatusPaneText(STATUS_PANE_SUM, (LPARAM)&dSum);
	else
		SetStatusPaneText(0, STATUS_PANE_SUM);
}

void TableView::SetStatusNumPaneText() const
{
	SetStatusPaneText(STATUS_PANE_NUM, GetListCtrl().GetItemCount());
}

LRESULT TableView::OnUmUpdateUI(WPARAM wp, LPARAM lp)
{
	GridView::OnUmUpdateUI(wp, lp);

	if(wp=UPDATE_UI_LANG)
	{
		m_rm.SetModified(ReloadMgr::oprEdit);

		if(((TSDIMVMainWndLang*)AfxGetMainWnd())->GetActiveView()==this)
			Reload();
	}

	return 0;
}
