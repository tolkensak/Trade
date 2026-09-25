
#include "stdafx.h"
#include "App.h"
#include "UserDlg.h"


BEGIN_MESSAGE_MAP(UserDlg, ManipDlg)
END_MESSAGE_MAP()


UserDlg::UserDlg(OBJID oidUser, CWnd* pParent /*=NULL*/)
	: ManipDlg(UserDlg::IDD, oidUser, pParent)
{
	m_rm.SetObject(ReloadMgr::objUser);
}

UserDlg::~UserDlg()
{
}
