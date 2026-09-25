
#include "stdafx.h"
#include "App.h"
#include "PasswordDlgSpec.h"


BEGIN_MESSAGE_MAP(PasswordDlgSpec, PasswordDlg)
END_MESSAGE_MAP()


PasswordDlgSpec::PasswordDlgSpec(OBJID oidUser, CWnd* pParent /*=NULL*/)
	: PasswordDlg(oidUser, pParent)
{
}

PasswordDlgSpec::~PasswordDlgSpec()
{
}

BOOL PasswordDlgSpec::OnInitDialog()
{
	PasswordDlg::OnInitDialog();

	CComboBox* pCb=(CComboBox*)GetDlgItem(IDC_CMB_USER);
	pCb->EnableWindow(FALSE);

	StringA stra;
	stra.Format("select id, login from `user` where id=%u", m_oid);
	Cb_Reload(pCb, stra, 0);

	return TRUE;
}
