
#include "stdafx.h"
#include "App.h"
#include "UnitCatDlg.h"


BEGIN_MESSAGE_MAP(UnitCatDlg, ManipDlg)
END_MESSAGE_MAP()


UnitCatDlg::UnitCatDlg(OBJID oidCat, CWnd* pParent /*=NULL*/)
	: ManipDlg(UnitCatDlg::IDD, oidCat, pParent)
{
	m_rm.SetObject(ReloadMgr::objUnitCat);
}

UnitCatDlg::~UnitCatDlg()
{
}
