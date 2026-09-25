
#include "stdafx.h"
#include "App.h"
#include "FirmView.h"
#include "FirmDlgNew.h"
#include "FirmDlgEdit.h"


IMPLEMENT_DYNCREATE(FirmView, ContactView)

BEGIN_MESSAGE_MAP(FirmView, ContactView)
END_MESSAGE_MAP()


FirmView::FirmView()
	: ContactView(IDR_FIRM, "firm")
{
	m_rm.SetObject(ReloadMgr::objFirm);
	m_straReload="call sp_firm_list(null)";
	m_straReloadRow="call sp_firm_list(%u)";

	int i=0;
	m_arrColumn.Add(Column(IDS_COL_NAME, Column::typeText, 140, i++));
	m_arrColumn.Add(Column(IDS_COL_WARE, Column::typeSymbol, 60, i++));
	m_arrColumn.Add(Column(IDS_COL_DISABLED, Column::typeBoolean, 70, i++));
}

FirmView::~FirmView()
{
}

BOOL FirmView::DataNew(OBJID& oid)
{
	FirmDlgNew dlg;
	if(dlg.DoModal()==IDOK)
	{
		oid=dlg.GetObjID();
		return TRUE;
	}

	return FALSE;
}

BOOL FirmView::DataEdit(OBJID& oid)
{
	FirmDlgEdit dlg(oid);
	if(dlg.DoModal()==IDOK)
	{
		oid=dlg.GetObjID();
		return TRUE;
	}

	return FALSE;
}
