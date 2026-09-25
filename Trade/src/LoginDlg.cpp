
#include "stdafx.h"
#include "App.h"
#include "LoginDlg.h"
#include "ConnectionDlg.h"


BEGIN_MESSAGE_MAP(LoginDlg, Dialog)
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()


LoginDlg::LoginDlg(CWnd* pParent)
	: Dialog(LoginDlg::IDD, pParent)
{
}

LoginDlg::~LoginDlg()
{
}

BOOL LoginDlg::OnInitDialog()
{
	Dialog::OnInitDialog();

	// Add "Connection" menu item to system menu.
	// IDM_CONNECTION must be in the system command range.
	ASSERT((IDM_CONNECTION&0xFFF0)==IDM_CONNECTION);
	ASSERT(IDM_CONNECTION<0xF000);

	CMenu* pSysMenu=GetSystemMenu(FALSE);
	if(pSysMenu)
	{
		CString cstr;
		cstr.LoadString(IDS_CONNECTION_MENU);
		if(cstr.IsEmpty())
			cstr=_T("Connection");

		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_CONNECTION, cstr);
	}

	return TRUE;
}

void LoginDlg::OnSysCommand(UINT uID, LPARAM lParam)
{
	if((uID&0xFFF0)==IDM_CONNECTION)
	{
		ConnectionDlg dlg;
		dlg.DoModal();
	}
	else
		CDialog::OnSysCommand(uID, lParam);
}

void LoginDlg::OnOK()
{
	CString cstrLogin;
	CString cstrPassword;

	GetDlgItemText(IDC_EDT_LOGIN, cstrLogin);
	GetDlgItemText(IDC_EDT_PASSWORD, cstrPassword);

	StringA stra;
	stra.Format("call sp_login('%s', fn_crypt_enc('%s'))", WcharToUtf8(cstrLogin), WcharToUtf8(cstrPassword));

	MySQLResPtr pRes=theApp.Query(stra, this);
	if(!pRes)
		return;

	MYSQL_ROW row=pRes->FetchRow();
	if(!row)
	{
		MsgBox(this, MB_ICONINFORMATION, IDS_BAD_LOGIN);
		return;
	}

	theApp.GetUser()(atoi(row[0]), atol(row[1]), atoi(row[2]));

	Dialog::OnOK();
}
