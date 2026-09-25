
#include "stdafx.h"
#include "App.h"
#include "PasswordDlg.h"


BEGIN_MESSAGE_MAP(PasswordDlg, ManipDlg)
END_MESSAGE_MAP()


PasswordDlg::PasswordDlg(OBJID oidUser, CWnd* pParent /*=NULL*/)
	: ManipDlg(PasswordDlg::IDD, oidUser, pParent)
{
	m_uTitleFormatID=IDS_TITLE_CHANGE;
}

PasswordDlg::~PasswordDlg()
{
}

void PasswordDlg::OnOK()
{
	if(m_oid==0)
	{
		ShowInfo(IDC_CMB_USER, IDS_BAD_SELECT);
		return;
	}

	ValidStr cstrPassword;
	GetDlgItemText(IDC_EDT_PASSWORD, cstrPassword);
	if(cstrPassword.IsEmpty())
	{
		ShowInfo(IDC_EDT_PASSWORD, IDS_BAD_TEXT);
		return;
	}

	CString cstrConfirmPassword;
	GetDlgItemText(IDC_EDT_CONFIRM_PASSWORD, cstrConfirmPassword);
	if(cstrConfirmPassword!=cstrPassword)
	{
		ShowInfo(IDC_EDT_CONFIRM_PASSWORD, IDS_BAD_CONFIRM_PASSWORD);
		return;
	}

	StringA stra;
	stra.Format("update `user` set pass=fn_crypt_enc('%s') where id=%u", WcharToUtf8(cstrPassword), m_oid);

	if(!theApp.Exec(stra, this))
		return;

	ManipDlg::OnOK();
}
