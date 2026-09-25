
#include "stdafx.h"
#include "App.h"
#include "WareCatDlg.h"


BEGIN_MESSAGE_MAP(WareCatDlg, ManipDlg)
END_MESSAGE_MAP()


WareCatDlg::WareCatDlg(OBJID oidCat, CWnd* pParent /*=NULL*/)
	: ManipDlg(WareCatDlg::IDD, oidCat, pParent)
{
	m_rm.SetObject(ReloadMgr::objWareCat);
}

WareCatDlg::~WareCatDlg()
{
}
