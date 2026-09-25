
#include "stdafx.h"
#include "App.h"
#include "ClientDlgEdit.h"


BEGIN_MESSAGE_MAP(ClientDlgEdit, ClientDlg)
END_MESSAGE_MAP()


ClientDlgEdit::ClientDlgEdit(OBJID oidClient, CWnd* pParent /*=NULL*/)
	: ClientDlg(oidClient, pParent)
{
	m_uTitleFormatID=IDS_TITLE_EDIT;
}

ClientDlgEdit::~ClientDlgEdit()
{
}

BOOL ClientDlgEdit::OnInitDialog()
{
	ClientDlg::OnInitDialog();

	StringA stra;
	stra.Format("call sp_client_edit(%u)", m_oid);

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
	SetDlgItemText(IDC_EDT_NAME, pch);

	i++;
	CheckDlgButton(IDC_CHK_DISABLED, atoi(row[i]));

	return TRUE;
}

void ClientDlgEdit::OnOK()
{
	ValidStr cstrName;
	GetDlgItemText(IDC_EDT_NAME, cstrName);
	if(!cstrName.IsValidName())
	{
		ShowInfo(IDC_EDT_NAME, IDS_BAD_TEXT);
		return;
	}

	StringA stra;
	stra.Format("update `client` set name='%s', disabled=%u where id=%u", WcharToUtf8(cstrName), IsDlgButtonChecked(IDC_CHK_DISABLED), m_oid);

	if(!theApp.Exec(stra, this))
		return;

	m_rm.SetModified(ReloadMgr::oprEdit);

	ClientDlg::OnOK();
}
