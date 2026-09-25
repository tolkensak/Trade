
#include "stdafx.h"
#include "App.h"
#include "AdvancedPermitDlgSpec.h"


BEGIN_MESSAGE_MAP(AdvancedPermitDlgSpec, AdvancedPermitDlg)
END_MESSAGE_MAP()


AdvancedPermitDlgSpec::AdvancedPermitDlgSpec(OBJID oidUser, CWnd* pParent /*=NULL*/)
	: AdvancedPermitDlg(oidUser, pParent)
{
}

AdvancedPermitDlgSpec::~AdvancedPermitDlgSpec()
{
}

BOOL AdvancedPermitDlgSpec::OnInitDialog()
{
	AdvancedPermitDlg::OnInitDialog();

	CComboBox* pCb=(CComboBox*)GetDlgItem(IDC_CMB_USER);
	pCb->EnableWindow(FALSE);

	StringA stra;
	stra.Format("select id, login from `user` where id=%u", m_oid);
	Cb_Reload(pCb, stra, 0);

	Reload();
	return TRUE;
}
