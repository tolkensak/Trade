
#include "stdafx.h"
#include "App.h"
#include "UserDlgNew.h"
#include "ContactDlgSpec.h"


BEGIN_MESSAGE_MAP(UserDlgNew, UserDlg)
END_MESSAGE_MAP()


UserDlgNew::UserDlgNew(CWnd* pParent /*=NULL*/)
	: UserDlg(0, pParent)
{
	m_uTitleFormatID=IDS_TITLE_NEW;
}

UserDlgNew::~UserDlgNew()
{
}

void UserDlgNew::OnOK()
{
	ValidStr cstrLogin;
	GetDlgItemText(IDC_EDT_LOGIN, cstrLogin);
	if(!cstrLogin.IsValidName())
	{
		ShowInfo(IDC_EDT_LOGIN, IDS_BAD_TEXT);
		return;
	}

	CString cstrPassword;
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
	stra.Format("insert into `user`(login, pass, disabled, uid) values('%s', fn_crypt_enc('%s'), %u, %u)"
		, WcharToUtf8(cstrLogin)
		, WcharToUtf8(cstrPassword)
		, IsDlgButtonChecked(IDC_CHK_DISABLED)
		, theApp.GetUser().GetID());

	m_oid=theApp.Insert(stra, this);
	if(m_oid==0)
		return;

	if(MsgBox(this, MB_YESNO|MB_ICONQUESTION, IDS_PROMPT_CONTACT_INFO, cstrLogin)==IDYES)
		SetContactInfo();

	m_rm.SetModified(ReloadMgr::oprNew);

	UserDlg::OnOK();
}

void UserDlgNew::SetContactInfo()
{
	StringA stra;
	stra.Format("select coid from `user` where id=%u", GetObjID());

	MySQLResPtr pRes=theApp.Query(stra, this);
	if(!pRes)
		return;

	MYSQL_ROW row=pRes->FetchRow();
	if(!row)
		return;

	ContactDlgSpec dlg(atoi(row[0]));
	dlg.DoModal();
}
