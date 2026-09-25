
#include "stdafx.h"
#include "App.h"
#include "MyPasswordDlg.h"


BEGIN_MESSAGE_MAP(MyPasswordDlg, Dialog)
END_MESSAGE_MAP()


MyPasswordDlg::MyPasswordDlg(CWnd* pParent /*=NULL*/)
	: Dialog(MyPasswordDlg::IDD, pParent)
{
	m_uTitleFormatID=IDS_TITLE_CHANGE;
}

MyPasswordDlg::~MyPasswordDlg()
{
}

void MyPasswordDlg::OnOK()
{
	ValidStr cstrOldPassword;
	GetDlgItemText(IDC_EDT_OLD_PASSWORD, cstrOldPassword);

	StringA stra;
	stra.Format("select count(*) from `user` where id=%u && pass=fn_crypt_enc('%s')", theApp.GetUser().GetID(), WcharToUtf8(cstrOldPassword));

	MySQLResPtr pRes=theApp.Query(stra, this);
	if(!pRes)
		return;

	MYSQL_ROW row=pRes->FetchRow();
	if(!row)
		return;

	if(atoi(row[0])==0)
	{
		ShowInfo(IDC_EDT_OLD_PASSWORD, IDS_BAD_OLD_PASSWORD);
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

	stra.Format("update `user` set pass=fn_crypt_enc('%s') where id=%u", WcharToUtf8(cstrPassword), theApp.GetUser().GetID());

	if(!theApp.Exec(stra, this))
		return;

	Dialog::OnOK();
}
