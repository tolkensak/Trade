
#include "stdafx.h"
#include "App.h"
#include "WareCatView.h"
#include "WareCatDlgNew.h"
#include "WareCatDlgEdit.h"


IMPLEMENT_DYNCREATE(WareCatView, TableView)

BEGIN_MESSAGE_MAP(WareCatView, TableView)
END_MESSAGE_MAP()


WareCatView::WareCatView()
	: TableView(IDR_WARE_CAT)
{
	m_rm.SetObject(ReloadMgr::objWareCat);
	m_straReload="call sp_ware_cat_list(null)";
	m_straReloadRow="call sp_ware_cat_list(%u)";

	int i=0;
	m_arrColumn.Add(Column(IDS_COL_NAME, Column::typeText, 140, i++));
	m_arrColumn.Add(Column(IDS_COL_WARE, Column::typeSymbol, 60, i++));
}

WareCatView::~WareCatView()
{
}

BOOL WareCatView::DataNew(OBJID& oid)
{
	WareCatDlgNew dlg;
	if(dlg.DoModal()==IDOK)
	{
		oid=dlg.GetObjID();
		return TRUE;
	}

	return FALSE;
}

BOOL WareCatView::DataEdit(OBJID& oid)
{
	WareCatDlgEdit dlg(oid);
	if(dlg.DoModal()==IDOK)
	{
		oid=dlg.GetObjID();
		return TRUE;
	}

	return FALSE;
}
