
#include "stdafx.h"
#include "App.h"
#include "UnitDlg.h"


BEGIN_MESSAGE_MAP(UnitDlg, ManipDlg)
END_MESSAGE_MAP()


UnitDlg::UnitDlg(OBJID oidUnit, CWnd* pParent /*=NULL*/)
	: ManipDlg(UnitDlg::IDD, oidUnit, pParent)
	, m_oidCat(0)
{
	m_rm.SetObject(ReloadMgr::objUnit);
}

UnitDlg::~UnitDlg()
{
}

void UnitDlg::ReloadCmbUnit()
{
	StringA stra;

	if(m_oidCat)
		stra.Format("select id, name from unit where ucid=%u && id!=%u order by main desc, ratio", m_oidCat, m_oid);

	CbReload(IDC_CMB_UNIT, stra, 0);
}
