
#include "stdafx.h"
#include "App.h"
#include "RunAsDlg.h"


BEGIN_MESSAGE_MAP(RunAsDlg, Dialog)
END_MESSAGE_MAP()


RunAsDlg::RunAsDlg(OBJID oidPermit, CWnd* pParent)
	: Dialog(RunAsDlg::IDD, pParent)
	, m_oidPermit(oidPermit)
{
}

RunAsDlg::~RunAsDlg()
{
}

void RunAsDlg::OnOK()
{
	CString cstrLogin;
	CString cstrPassword;

	GetDlgItemText(IDC_EDT_LOGIN, cstrLogin);
	GetDlgItemText(IDC_EDT_PASSWORD, cstrPassword);

	StringA stra;
	stra.Format("call sp_run_as('%s', fn_crypt_enc('%s'))", WcharToUtf8(cstrLogin), WcharToUtf8(cstrPassword));

	MySQLResPtr pRes=theApp.Query(stra, this);
	if(!pRes)
		return;

	MYSQL_ROW row=pRes->FetchRow();
	if(!row)
	{
		MsgBox(this, MB_ICONINFORMATION, IDS_BAD_LOGIN);
		return;
	}

	if((m_oidPermit&atol(row[0]))!=m_oidPermit)
	{
		MsgBox(GetOwner(), MB_ICONINFORMATION, IDS_ERR_NO_PERMIT);
		return;
	}

	Dialog::OnOK();
}
