
#include "stdafx.h"
#include "App.h"
#include "WareCatDlgEdit.h"


BEGIN_MESSAGE_MAP(WareCatDlgEdit, WareCatDlg)
END_MESSAGE_MAP()


WareCatDlgEdit::WareCatDlgEdit(OBJID oidCat, CWnd* pParent /*=NULL*/)
	: WareCatDlg(oidCat, pParent)
{
	m_uTitleFormatID=IDS_TITLE_EDIT;
}

WareCatDlgEdit::~WareCatDlgEdit()
{
}

BOOL WareCatDlgEdit::OnInitDialog()
{
	WareCatDlg::OnInitDialog();

	StringA stra;
	stra.Format("call sp_ware_cat_edit(%u)", m_oid);

	MySQLResPtr pRes=theApp.Query(stra, this);
	if(!pRes)
		return TRUE;

	MYSQL_ROW row=pRes->FetchRow();
	if(!row)
		return TRUE;

	TCHAR pch[TOL_MAXSTR];
	PULONG len=pRes->FetchLengths();

	Utf8ToWchar(row[0], len[0], pch);
	SetDlgItemText(IDC_EDT_NAME, pch);

	return TRUE;
}

void WareCatDlgEdit::OnOK()
{
	ValidStr cstrName;
	GetDlgItemText(IDC_EDT_NAME, cstrName);
	if(!cstrName.IsValidName())
	{
		ShowInfo(IDC_EDT_NAME, IDS_BAD_TEXT);
		return;
	}

	StringA stra;
	stra.Format("update ware_cat set name='%s' where id=%u", WcharToUtf8(cstrName), m_oid);

	if(!theApp.Exec(stra, this))
		return;

	m_rm.SetModified(ReloadMgr::oprEdit);

	WareCatDlg::OnOK();
}
