
#include "stdafx.h"
#include "App.h"
#include "EasyPermitDlgGlob.h"
#include "AdvancedPermitDlgGlob.h"


BEGIN_MESSAGE_MAP(EasyPermitDlgGlob, EasyPermitDlg)
	ON_CBN_SELCHANGE(IDC_CMB_USER, &EasyPermitDlgGlob::OnCbnSelChangeCmbUser)
	ON_BN_CLICKED(IDC_BTN_ADVANCED, &EasyPermitDlgGlob::OnBnClickedBtnAdvanced)
END_MESSAGE_MAP()


EasyPermitDlgGlob::EasyPermitDlgGlob(CWnd* pParent /*=NULL*/)
	: EasyPermitDlg(0, pParent)
{
}

EasyPermitDlgGlob::~EasyPermitDlgGlob()
{
}

void EasyPermitDlgGlob::OnCbnSelChangeCmbUser()
{
	m_oid=CbGetOid(IDC_CMB_USER);
	Reload();
}

BOOL EasyPermitDlgGlob::OnInitDialog()
{
	EasyPermitDlg::OnInitDialog();
	CbReload(IDC_CMB_USER, "select id, login from `user` order by name", -1, m_oid);

	Reload();
	return TRUE;
}

void EasyPermitDlgGlob::OnBnClickedBtnAdvanced()
{
	AdvancedPermitDlgGlob dlg;
	dlg.SetUser(m_oid, m_dwPermit);

	if(dlg.DoModal()==IDOK)
		EndDialog(IDOK);
	else
	{
		SetUser(dlg);
		Reload();
	}
}
