
#include "stdafx.h"
#include "App.h"
#include "PasswordDlgGlob.h"


BEGIN_MESSAGE_MAP(PasswordDlgGlob, PasswordDlg)
	ON_CBN_SELCHANGE(IDC_CMB_USER, &PasswordDlgGlob::OnCbnSelChangeCmbUser)
END_MESSAGE_MAP()


PasswordDlgGlob::PasswordDlgGlob(CWnd* pParent /*=NULL*/)
	: PasswordDlg(0, pParent)
{
}

PasswordDlgGlob::~PasswordDlgGlob()
{
}

void PasswordDlgGlob::OnCbnSelChangeCmbUser()
{
	m_oid=CbGetOid(IDC_CMB_USER);
}

BOOL PasswordDlgGlob::OnInitDialog()
{
	PasswordDlg::OnInitDialog();
	CbReload(IDC_CMB_USER, "select id, login from `user` order by name", -1, m_oid);
	return TRUE;
}
