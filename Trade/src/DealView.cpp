
#include "stdafx.h"
#include "App.h"
#include "DealView.h"


BEGIN_MESSAGE_MAP(DealView, TableView)
	ON_COMMAND(ID_DATA_SUBMIT, &DealView::OnDataSubmit)
	ON_UPDATE_COMMAND_UI(ID_DATA_SUBMIT, &DealView::OnUpdateDataSubmit)
END_MESSAGE_MAP()


DealView::DealView(UINT uUniqueID, PCCharA pcTablePrefix)
	: TableView(uUniqueID)
	, m_straTablePrefix(pcTablePrefix)
	, m_oidLot(0)
{
}

DealView::~DealView()
{
}

void DealView::ReloadLot(OBJID oidDeal)
{
	OBJID oidLot=0;

	StringA stra;
	stra.Format("call sp_%s_lot_present(%u, %u)", (PCCharA)m_straTablePrefix, oidDeal, theApp.GetUser().GetID());

	MySQLResPtr pRes=theApp.Query(stra, this);
	if(pRes)
	{
		MYSQL_ROW row=pRes->FetchRow();
		if(row)
			oidLot=atoi(row[0]);
	}

	ChangeLot(oidLot);
}

void DealView::ChangeLot(OBJID oidLot)
{
	m_oidLot=oidLot;
	m_straReload.Format("call sp_%s_lot_list(%u, NULL)", (PCCharA)m_straTablePrefix, m_oidLot);
	m_straReloadRow.Format("call sp_%s_lot_list(%u, %%u)", (PCCharA)m_straTablePrefix, m_oidLot);
}

void DealView::OnInitialUpdate()
{
	TableView::OnInitialUpdate();
	ReloadLot();
}

BOOL DealView::ContextMenu(HMENU hMenu, UINT* puFlags, int iItem)
{
	if(!TableView::ContextMenu(hMenu, puFlags, iItem))
		return FALSE;

	HMENU hMenuMain=AfxGetMainWnd()->GetMenu()->GetSafeHmenu();
	if(hMenuMain)
	{
		AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
		Menu_CopyItem(hMenu, -1, hMenuMain, ID_DATA_SUBMIT, TRUE);
	}

	return TRUE;
}

BOOL DealView::GetSum(double& dSum) const
{
	StringA stra;
	stra.Format("call sp_%s_lot_sum_total(%u)", (PCCharA)m_straTablePrefix, m_oidLot);

	MySQLResPtr pRes=theApp.Query(stra,  const_cast<DealView*>(this));
	if(!pRes)
		return FALSE;

	MYSQL_ROW row=pRes->FetchRow();
	if(!row)
		return FALSE;

	dSum=atof(row[0]);
	return TRUE;
}

void DealView::OnDataSubmit()
{
	if(MsgBox(this, MB_YESNO|MB_ICONQUESTION, IDS_PROMPT_SUBMIT_DEAL)==IDNO)
		return;

	StringA stra;
	stra.Format("call sp_%s_lot_submit(%u)", (PCCharA)m_straTablePrefix, m_oidLot);

	if(!theApp.Exec(stra, this))
		return;

	ChangeLot(0);
	Reload();
}

void DealView::OnUpdateDataSubmit(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetListCtrl().GetItemCount());
}
