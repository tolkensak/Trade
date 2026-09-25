
#include "stdafx.h"
#include "App.h"
#include "SellView.h"
#include "SellDlgNew.h"
#include "SellDlgEdit.h"
#include "SellDebtDlg.h"
#include "SellReturnDlg.h"
#include "Indent.h"
#include "Report.h"


IMPLEMENT_DYNCREATE(SellView, DealView)

BEGIN_MESSAGE_MAP(SellView, DealView)
	ON_COMMAND(ID_DATA_SELL_DEBT, &SellView::OnDataSellDebt)
	ON_COMMAND(ID_DATA_SELL_RETURN, &SellView::OnDataSellReturn)
	ON_COMMAND(ID_DATA_SUBMIT, &SellView::OnDataSubmit)
	ON_COMMAND(ID_DATA_STOP_FILL, &SellView::OnDataStopFill)
	ON_UPDATE_COMMAND_UI(ID_DATA_STOP_FILL, &SellView::OnUpdateDataStopFill)
	ON_COMMAND(ID_DATA_VIEW, &SellView::OnDataView)
	ON_UPDATE_COMMAND_UI(ID_DATA_VIEW, &SellView::OnUpdateDataView)
	ON_COMMAND(ID_DATA_EXPORT, &SellView::OnDataExport)
	ON_UPDATE_COMMAND_UI(ID_DATA_EXPORT, &SellView::OnUpdateDataExport)
	ON_MESSAGE(UM_VIEW_ACTIVATED, &SellView::OnViewActivated)
	ON_MESSAGE(UM_UPDATE_UI, &SellView::OnUmUpdateUI)
END_MESSAGE_MAP()


SellView::SellView()
	: DealView(IDR_SELL, "sell")
{
	m_rm.SetObject(ReloadMgr::objSell);

	int i=0;
	m_arrColumn.Add(Column(IDS_COL_WARE, Column::typeText, 140, i++));
	m_arrColumn.Add(Column(IDS_COL_CAT, Column::typeText, 100, i++));
	m_arrColumn.Add(Column(IDS_COL_AMOUNT, Column::typeFloat, 70, i++));
	m_arrColumn.Add(Column(IDS_COL_UNIT, Column::typeSymbol, 70, i++));
	m_arrColumn.Add(Column(IDS_COL_PRICE, Column::typeMoney, 100, i++));
	m_arrColumn.Add(Column(IDS_COL_TOTAL, Column::typeMoney, 100, i++));
	m_arrColumn.Add(Column(IDS_COL_DEBT, Column::typeText, 100, i++));
	m_arrColumn.Add(Column(IDS_COL_MOMENT, Column::typeDateTime, 100, i++));
}

SellView::~SellView()
{
}

void SellView::SetTitle(BOOL bSet)
{
	if(bSet)
	{
		if(m_oidLot!=theIndent.GetLotID())
			return;

		CString str;
		str.LoadString(IDS_TITLE_INDENT);

		CString strTitle;
		strTitle.Format(_T("%s %s"), str, theIndent.GetID());

		TSDIMVMainWndLang* pMainWnd=(TSDIMVMainWndLang*)AfxGetMainWnd();
		pMainWnd->SetTitle(strTitle);
		pMainWnd->OnUpdateFrameTitle(TRUE);
	}
	else
	{
		CString str;
		theApp.GetTemplate(this)->GetDocString(str, CDocTemplate::windowTitle);

		TSDIMVMainWndLang* pMainWnd=(TSDIMVMainWndLang*)AfxGetMainWnd();
		pMainWnd->SetTitle(str);
		pMainWnd->OnUpdateFrameTitle(TRUE);
	}
}

LRESULT SellView::OnViewActivated(WPARAM wp, LPARAM lp)
{
	OBJID oidLotIndent=theIndent.GetLotID();

	if(theIndent.IsChanged())
	{
		if(oidLotIndent==-1)
			ReloadLot();
		else
			ChangeLot(oidLotIndent);

		theIndent.ApplyChange();
		wp=1;
	}

	SetTitle();

	return DealView::OnViewActivated(wp, lp);
}

BOOL SellView::DataNew(OBJID& oid)
{
	SellDlgNew dlg(m_oidLot);
	if(dlg.DoModal()==IDOK)
	{
		oid=dlg.GetObjID();

		if(m_oidLot==0)
			ReloadLot(oid);

		return TRUE;
	}

	return FALSE;
}

BOOL SellView::DataEdit(OBJID& oid)
{
	SellDlgEdit dlg(oid);
	if(dlg.DoModal()==IDOK)
	{
		oid=dlg.GetObjID();
		return TRUE;
	}

	return FALSE;
}

void SellView::OnDataSellDebt()
{
	SellDebtDlg dlg;
	dlg.DoModal();
}

void SellView::OnDataSellReturn()
{
	SellReturnDlg dlg;
	dlg.DoModal();
}

void SellView::OnDataStopFill()
{
	if(m_oidLot!=theIndent.GetLotID())
		return;

	SetTitle(FALSE);

	theIndent(FALSE);

	ReloadLot();
	Reload();
}

void SellView::OnUpdateDataStopFill(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_oidLot==theIndent.GetLotID());
}

void SellView::OnDataView()
{
	if(m_oidLot==theIndent.GetLotID())
		Invoice_Show(m_oidLot, this);
}

void SellView::OnUpdateDataView(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_oidLot==theIndent.GetLotID());
}

void SellView::OnDataExport()
{
	if(m_oidLot==theIndent.GetLotID())
		Invoice_Export(m_oidLot, this);
}

void SellView::OnUpdateDataExport(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_oidLot==theIndent.GetLotID());
}

void SellView::OnDataSubmit()
{
	if(m_oidLot==theIndent.GetLotID())
	{
		if(MsgBox(this, MB_YESNO|MB_ICONQUESTION, IDS_PROMPT_SUBMIT_INDENT)==IDNO)
			return;

		StringA stra;
		stra.Format("call sp_indent_submit(%u)", m_oidLot);

		if(!theApp.Exec(stra, this))
			return;

		ReloadMgr rm(ReloadMgr::objIndent);
		rm.SetModified(ReloadMgr::oprEdit);

		SetTitle(FALSE);

		ReloadLot();
		Reload();
	}
	else
		DealView::OnDataSubmit();
}

LRESULT SellView::OnUmUpdateUI(WPARAM wp, LPARAM lp)
{
	DealView::OnUmUpdateUI(wp, lp);

	if(wp=UPDATE_UI_LANG)
		SetTitle();

	return 0;
}
