
#include "stdafx.h"
#include "App.h"
#include "WareView.h"
#include "WareDlgNew.h"
#include "WareDlgEdit.h"
#include "PriceDlgSpec.h"


IMPLEMENT_DYNCREATE(WareView, TableView)

BEGIN_MESSAGE_MAP(WareView, TableView)
	ON_COMMAND(ID_DATA_PRICE, &WareView::OnDataPrice)
	ON_UPDATE_COMMAND_UI(ID_DATA_PRICE, &WareView::OnUpdateDataPrice)
END_MESSAGE_MAP()


WareView::WareView()
	: TableView(IDR_WARE)
{
	m_rm.SetObject(ReloadMgr::objWare);
	m_straReload="call sp_ware_list(null)";
	m_straReloadRow="call sp_ware_list(%u)";

	int i=0;
	m_arrColumn.Add(Column(IDS_COL_NAME, Column::typeText, 140, i++));
	m_arrColumn.Add(Column(IDS_COL_PRICE, Column::typeMoney, 100, i++));
	m_arrColumn.Add(Column(IDS_COL_CAT, Column::typeText, 100, i++));
	m_arrColumn.Add(Column(IDS_COL_FIRM, Column::typeText, 100, i++));
	m_arrColumn.Add(Column(IDS_COL_UNIT_CAT, Column::typeText, 100, i++));
}

WareView::~WareView()
{
}

BOOL WareView::ContextMenu(HMENU hMenu, UINT* puFlags, int iItem)
{
	if(!TableView::ContextMenu(hMenu, puFlags, iItem))
		return FALSE;

	HMENU hMenuMain=AfxGetMainWnd()->GetMenu()->GetSafeHmenu();
	if(hMenuMain)
	{
		AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
		Menu_CopyItem(hMenu, -1, hMenuMain, ID_DATA_PRICE, TRUE);
	}

	return TRUE;
}

BOOL WareView::DataNew(OBJID& oid)
{
	WareDlgNew dlg;
	if(dlg.DoModal()==IDOK)
	{
		oid=dlg.GetObjID();
		return TRUE;
	}

	return FALSE;
}

BOOL WareView::DataEdit(OBJID& oid)
{
	WareDlgEdit dlg(oid);
	if(dlg.DoModal()==IDOK)
	{
		oid=dlg.GetObjID();
		return TRUE;
	}

	return FALSE;
}

void WareView::OnDataPrice()
{
	OBJID oid=GetFirstSelectedItemObjID();
	if(oid)
	{
		PriceDlgSpec dlg(oid);
		if(dlg.DoModal()==IDOK)
			Reload(dlg.GetObjID());
	}
}

void WareView::OnUpdateDataPrice(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetListCtrl().GetSelectedCount()==1);
}
