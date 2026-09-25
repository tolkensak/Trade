
#include "stdafx.h"
#include "App.h"
#include "EasyPermitDlgSpec.h"
#include "AdvancedPermitDlgSpec.h"


BEGIN_MESSAGE_MAP(EasyPermitDlgSpec, EasyPermitDlg)
	ON_BN_CLICKED(IDC_BTN_ADVANCED, &EasyPermitDlgSpec::OnBnClickedBtnAdvanced)
END_MESSAGE_MAP()


EasyPermitDlgSpec::EasyPermitDlgSpec(OBJID oidUser, CWnd* pParent /*=NULL*/)
	: EasyPermitDlg(oidUser, pParent)
{
}

EasyPermitDlgSpec::~EasyPermitDlgSpec()
{
}

BOOL EasyPermitDlgSpec::OnInitDialog()
{
	EasyPermitDlg::OnInitDialog();

	CComboBox* pCb=(CComboBox*)GetDlgItem(IDC_CMB_USER);
	pCb->EnableWindow(FALSE);

	StringA stra;
	stra.Format("select id, login from `user` where id=%u", m_oid);
	Cb_Reload(pCb, stra, 0);

	Reload();
	return TRUE;
}

void EasyPermitDlgSpec::OnBnClickedBtnAdvanced()
{
	AdvancedPermitDlgSpec dlg(m_oid);
	dlg.SetUser(m_oid, m_dwPermit);

	if(dlg.DoModal()==IDOK)
		EndDialog(IDOK);
	else
	{
		SetUser(dlg);
		Reload();
	}
}
