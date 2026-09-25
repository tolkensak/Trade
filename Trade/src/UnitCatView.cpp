
#include "stdafx.h"
#include "App.h"
#include "UnitCatView.h"
#include "UnitCatDlgNew.h"
#include "UnitCatDlgEdit.h"


IMPLEMENT_DYNCREATE(UnitCatView, TableView)

BEGIN_MESSAGE_MAP(UnitCatView, TableView)
END_MESSAGE_MAP()


UnitCatView::UnitCatView()
	: TableView(IDR_UNIT_CAT)
{
	m_rm.SetObject(ReloadMgr::objUnitCat);
	m_straReload="call sp_unit_cat_list(null)";
	m_straReloadRow="call sp_unit_cat_list(%u)";

	int i=0;
	m_arrColumn.Add(Column(IDS_COL_NAME, Column::typeText, 140, i++));
	m_arrColumn.Add(Column(IDS_COL_MAIN_UNIT, Column::typeSymbol, 60, i++));
}

UnitCatView::~UnitCatView()
{
}

BOOL UnitCatView::DataNew(OBJID& oid)
{
	UnitCatDlgNew dlg;
	if(dlg.DoModal()==IDOK)
	{
		oid=dlg.GetObjID();
		return TRUE;
	}

	return FALSE;
}

BOOL UnitCatView::DataEdit(OBJID& oid)
{
	UnitCatDlgEdit dlg(oid);
	if(dlg.DoModal()==IDOK)
	{
		oid=dlg.GetObjID();
		return TRUE;
	}

	return FALSE;
}
