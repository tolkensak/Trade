
#include "stdafx.h"
#include "App.h"
#include "AdvancedPermitDlgGlob.h"


BEGIN_MESSAGE_MAP(AdvancedPermitDlgGlob, AdvancedPermitDlg)
	ON_CBN_SELCHANGE(IDC_CMB_USER, &AdvancedPermitDlgGlob::OnCbnSelChangeCmbUser)
END_MESSAGE_MAP()


AdvancedPermitDlgGlob::AdvancedPermitDlgGlob(CWnd* pParent /*=NULL*/)
	: AdvancedPermitDlg(0, pParent)
{
}

AdvancedPermitDlgGlob::~AdvancedPermitDlgGlob()
{
}

void AdvancedPermitDlgGlob::OnCbnSelChangeCmbUser()
{
	m_oid=CbGetOid(IDC_CMB_USER);
	Reload();
}

BOOL AdvancedPermitDlgGlob::OnInitDialog()
{
	AdvancedPermitDlg::OnInitDialog();
	CbReload(IDC_CMB_USER, "select id, login from `user` order by name", -1, m_oid);
	Reload();
	return TRUE;
}
