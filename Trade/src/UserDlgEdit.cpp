
#include "stdafx.h"
#include "App.h"
#include "UserDlgEdit.h"


BEGIN_MESSAGE_MAP(UserDlgEdit, UserDlg)
END_MESSAGE_MAP()


UserDlgEdit::UserDlgEdit(OBJID oidUser, CWnd* pParent /*=NULL*/)
	: UserDlg(oidUser, pParent)
{
	m_uTitleFormatID=IDS_TITLE_EDIT;
}

UserDlgEdit::~UserDlgEdit()
{
}

BOOL UserDlgEdit::OnInitDialog()
{
	UserDlg::OnInitDialog();

	CRect rc;
	GetDlgItem(IDC_EDT_PASSWORD)->GetWindowRect(&rc);
	int dy=rc.top;

	CWnd* pWndAncor=GetDlgItem(IDC_CHK_DISABLED);
	pWndAncor->GetWindowRect(&rc);
	dy-=rc.top;

	// pWndAncor=pWndAncor->GetNextWindow(GW_HWNDPREV); // label of pWndAncor

	CWnd* pWnd=GetDlgItem(IDC_EDT_LOGIN)->GetNextWindow();
	while(pWnd)
	{
		if(pWnd==pWndAncor)
			break;

		pWnd->EnableWindow(FALSE);
		pWnd->ShowWindow(SW_HIDE);
		pWnd=pWnd->GetNextWindow();
	}

	while(pWnd)
	{
		pWnd->GetWindowRect(&rc);
		rc.OffsetRect(0, dy);
		ScreenToClient(&rc);
		pWnd->MoveWindow(&rc);
		pWnd=pWnd->GetNextWindow();
	}

	GetWindowRect(&rc);
	rc.bottom+=dy;
	MoveWindow(&rc);



	StringA stra;
	stra.Format("call sp_user_edit(%u)", m_oid);

	MySQLResPtr pRes=theApp.Query(stra, this);
	if(!pRes)
		return TRUE;

	MYSQL_ROW row=pRes->FetchRow();
	if(!row)
		return TRUE;

	TCHAR pch[TOL_MAXSTR];
	PULONG len=pRes->FetchLengths();

	int i=0;
	Utf8ToWchar(row[i], len[i], pch);
	SetDlgItemText(IDC_EDT_LOGIN, pch);

	i++;
	CheckDlgButton(IDC_CHK_DISABLED, atoi(row[i]));

	return TRUE;
}

void UserDlgEdit::OnOK()
{
	if(m_oid==1)
	{
		MsgBox(this, MB_ICONINFORMATION, IDS_ERR_TOUCH_ROOT);
		return;
	}

	ValidStr cstrLogin;
	GetDlgItemText(IDC_EDT_LOGIN, cstrLogin);
	if(!cstrLogin.IsValidName())
	{
		ShowInfo(IDC_EDT_LOGIN, IDS_BAD_TEXT);
		return;
	}

	StringA stra;
	stra.Format("update `user` set login='%s', disabled=%u where id=%u", WcharToUtf8(cstrLogin), IsDlgButtonChecked(IDC_CHK_DISABLED), m_oid);

	if(!theApp.Exec(stra, this))
		return;

	m_rm.SetModified(ReloadMgr::oprEdit);

	UserDlg::OnOK();
}
