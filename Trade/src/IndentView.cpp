
#include "stdafx.h"
#include "App.h"
#include "IndentView.h"
#include "IndentDlgNew.h"
#include "IndentDlgEdit.h"
#include "Indent.h"
#include "Report.h"


IMPLEMENT_DYNCREATE(IndentView, TableView)

BEGIN_MESSAGE_MAP(IndentView, TableView)
	ON_COMMAND(ID_DATA_SUBMIT, &IndentView::OnDataSubmit)
	ON_UPDATE_COMMAND_UI(ID_DATA_SUBMIT, &IndentView::OnUpdateDataSubmit)
	ON_COMMAND(ID_DATA_FILL, &IndentView::OnDataFill)
	ON_UPDATE_COMMAND_UI(ID_DATA_FILL, &IndentView::OnUpdateDataFill)
	ON_COMMAND(ID_DATA_VIEW, &IndentView::OnDataView)
	ON_UPDATE_COMMAND_UI(ID_DATA_VIEW, &IndentView::OnUpdateDataView)
	ON_COMMAND(ID_DATA_EXPORT, &IndentView::OnDataExport)
	ON_UPDATE_COMMAND_UI(ID_DATA_EXPORT, &IndentView::OnUpdateDataExport)
END_MESSAGE_MAP()


IndentView::IndentView()
	: TableView(IDR_INDENT)
{
	m_rm.SetObject(ReloadMgr::objIndent);
	m_straReload="call sp_indent_list(null)";
	m_straReloadRow="call sp_indent_list(%u)";

	int i=0;
	m_arrColumn.Add(Column(IDS_COL_ID, Column::typeSymbol, 80, i++));
	m_arrColumn.Add(Column(IDS_COL_CLIENT, Column::typeText, 120, i++));
	m_arrColumn.Add(Column(IDS_COL_DELIVER, Column::typeDate, 100, i++));
	m_arrColumn.Add(Column(IDS_COL_MOMENT, Column::typeDateTime, 100, i++));
}

IndentView::~IndentView()
{
}

BOOL IndentView::ContextMenu(HMENU hMenu, UINT* puFlags, int iItem)
{
	if(!TableView::ContextMenu(hMenu, puFlags, iItem))
		return FALSE;

	HMENU hMenuMain=AfxGetMainWnd()->GetMenu()->GetSafeHmenu();
	if(hMenuMain)
	{
		AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
		Menu_CopyItem(hMenu, -1, hMenuMain, ID_DATA_FILL, TRUE);
		Menu_CopyItem(hMenu, -1, hMenuMain, ID_DATA_VIEW, TRUE);
		Menu_CopyItem(hMenu, -1, hMenuMain, ID_DATA_SUBMIT, TRUE);
	}

	return TRUE;
}

BOOL IndentView::DataNew(OBJID& oid)
{
	IndentDlgNew dlg;
	if(dlg.DoModal()==IDOK)
	{
		oid=dlg.GetObjID();
		return TRUE;
	}

	return FALSE;
}

BOOL IndentView::DataEdit(OBJID& oid)
{
	IndentDlgEdit dlg(oid);
	if(dlg.DoModal()==IDOK)
	{
		oid=dlg.GetObjID();
		return TRUE;
	}

	return FALSE;
}

BOOL IndentView::DataSubmit(int* pnSubmit, int nCount)
{
	if(!pnSubmit || !nCount)
		return FALSE;

	if(MsgBox(this, MB_YESNO|MB_ICONQUESTION, IDS_PROMPT_SUBMIT_INDENT)==IDNO)
		return FALSE;

	const Connection& conn=theApp.Connect();
	if(!conn)
		return FALSE;

	StringA stra;
	OBJID oidLot;
	MySQLResPtr pRes;
	MYSQL_ROW row;
	BOOL bRet=FALSE;

	for(int i=0; i<nCount; i++)
	{
		oidLot=GetItemObjID(pnSubmit[i]);

		stra.Format("select count(*) from sell_lot where lid=%u ", oidLot);

		pRes=theApp.Query(stra, this);
		if(!pRes)
			continue;

		row=pRes->FetchRow();
		if(!row)
			continue;

		if(atoi(row[0])==0)
		{
			MsgBox(this, MB_ICONINFORMATION, IDS_ERR_EMPTY_INDENT, GetListCtrl().GetItemText(pnSubmit[i], 0));
			continue;
		}


		stra.Format("call sp_indent_submit(%u)", oidLot);

		if(theApp.Exec(stra, this))
		{
			bRet=TRUE;

			if(oidLot==theIndent.GetLotID())
				theIndent();
		}
		else
			pnSubmit[i]=-1;
	}

	return bRet;
}

void IndentView::OnDataSubmit()
{
	CListCtrl& lc=GetListCtrl();
	int i=lc.GetSelectedCount();
	if(i==0)
		return;

	int* pn=new int[i];
	POSITION pos=lc.GetFirstSelectedItemPosition();
	i=0;
	while(pos)
		pn[i++]=lc.GetNextSelectedItem(pos);

	if(DataSubmit(pn, i))
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

void IndentView::OnUpdateDataSubmit(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetListCtrl().GetSelectedCount());
}

void IndentView::OnDataFill()
{
	CListCtrl& lc=GetListCtrl();

	int nItem=GetFirstSelectedItem();
	if(nItem==-1)
		return;

	OBJID oidLot=GetItemObjID(nItem);
	if(oidLot==0)
		return;

	if(oidLot==theIndent.GetLotID())
		theIndent();
	else
	{
		theIndent(TRUE, oidLot, lc.GetItemText(nItem, 0));
		AfxGetMainWnd()->SendMessage(WM_COMMAND, MAKEWPARAM(GetDeskCmdID(IDR_SELL), 0));
	}
}

void IndentView::OnUpdateDataFill(CCmdUI *pCmdUI)
{
	if(GetListCtrl().GetSelectedCount()==1)
	{
		pCmdUI->Enable(TRUE);
		pCmdUI->SetCheck(GetFirstSelectedItemObjID()==theIndent.GetLotID());
	}
	else
	{
		pCmdUI->Enable(FALSE);
		pCmdUI->SetCheck(FALSE);
	}
}

void IndentView::OnDataView()
{
	CListCtrl& lc=GetListCtrl();
	if(lc.GetSelectedCount()!=1)
		return;

	OBJID oid=GetFirstSelectedItemObjID();
	if(oid==0)
		return;

	Invoice_Show(oid, this);
}

void IndentView::OnUpdateDataView(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetListCtrl().GetSelectedCount()==1);
}

void IndentView::OnDataExport()
{
	CListCtrl& lc=GetListCtrl();
	if(lc.GetSelectedCount()!=1)
		return;

	OBJID oid=GetFirstSelectedItemObjID();
	if(oid==0)
		return;

	Invoice_Export(oid, this);
}

void IndentView::OnUpdateDataExport(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetListCtrl().GetSelectedCount()==1);
}
