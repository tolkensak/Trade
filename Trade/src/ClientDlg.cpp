
#include "stdafx.h"
#include "App.h"
#include "ClientDlg.h"


BEGIN_MESSAGE_MAP(ClientDlg, ManipDlg)
END_MESSAGE_MAP()


ClientDlg::ClientDlg(OBJID oidClient, CWnd* pParent /*=NULL*/)
	: ManipDlg(ClientDlg::IDD, oidClient, pParent)
{
	m_rm.SetObject(ReloadMgr::objClient);
}

ClientDlg::~ClientDlg()
{
}
