
#include "stdafx.h"
#include "App.h"
#include "ClientView.h"
#include "ClientDlgNew.h"
#include "ClientDlgEdit.h"


IMPLEMENT_DYNCREATE(ClientView, ContactView)

BEGIN_MESSAGE_MAP(ClientView, ContactView)
END_MESSAGE_MAP()


ClientView::ClientView()
	: ContactView(IDR_CLIENT, "`client`")
{
	m_rm.SetObject(ReloadMgr::objClient);
	m_straReload="call sp_client_list(null)";
	m_straReloadRow="call sp_client_list(%u)";

	int i=0;
	m_arrColumn.Add(Column(IDS_COL_NAME, Column::typeText, 140, i++));
	m_arrColumn.Add(Column(IDS_COL_DISABLED, Column::typeBoolean, 70, i++));
}

ClientView::~ClientView()
{
}

BOOL ClientView::DataNew(OBJID& oid)
{
	ClientDlgNew dlg;
	if(dlg.DoModal()==IDOK)
	{
		oid=dlg.GetObjID();
		return TRUE;
	}

	return FALSE;
}

BOOL ClientView::DataEdit(OBJID& oid)
{
	ClientDlgEdit dlg(oid);
	if(dlg.DoModal()==IDOK)
	{
		oid=dlg.GetObjID();
		return TRUE;
	}

	return FALSE;
}
