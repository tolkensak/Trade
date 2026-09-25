
#include "stdafx.h"
#include "App.h"
#include "UnitView.h"
#include "UnitDlgNew.h"
#include "UnitDlgEdit.h"


IMPLEMENT_DYNCREATE(UnitView, TableView)

BEGIN_MESSAGE_MAP(UnitView, TableView)
END_MESSAGE_MAP()


UnitView::UnitView()
	: TableView(IDR_UNIT)
{
	m_rm.SetObject(ReloadMgr::objUnit);
	m_straReload="call sp_unit_list(null)";
	m_straReloadRow="call sp_unit_list(%u)";

	int i=0;
	m_arrColumn.Add(Column(IDS_COL_NAME, Column::typeText, 60, i++));
	m_arrColumn.Add(Column(IDS_COL_RATIO, Column::typeFloat, 80, i++));
	m_arrColumn.Add(Column(IDS_COL_MAIN_UNIT, Column::typeSymbol, 60, i++));
	m_arrColumn.Add(Column(IDS_COL_CAT, Column::typeText, 140, i++));
}

UnitView::~UnitView()
{
}

BOOL UnitView::DataNew(OBJID& oid)
{
	UnitDlgNew dlg;
	if(dlg.DoModal()==IDOK)
	{
		oid=dlg.GetObjID();
		return TRUE;
	}

	return FALSE;
}

BOOL UnitView::DataEdit(OBJID& oid)
{
	UnitDlgEdit dlg(oid);
	if(dlg.DoModal()==IDOK)
	{
		oid=dlg.GetObjID();
		return TRUE;
	}

	return FALSE;
}
