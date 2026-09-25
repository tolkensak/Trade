
#include "stdafx.h"
#include "App.h"
#include "FirmDlg.h"


BEGIN_MESSAGE_MAP(FirmDlg, ManipDlg)
END_MESSAGE_MAP()


FirmDlg::FirmDlg(OBJID oidFirm, CWnd* pParent /*=NULL*/)
	: ManipDlg(FirmDlg::IDD, oidFirm, pParent)
{
	m_rm.SetObject(ReloadMgr::objFirm);
}

FirmDlg::~FirmDlg()
{
}
