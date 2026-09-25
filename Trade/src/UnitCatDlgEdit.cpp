
#include "stdafx.h"
#include "App.h"
#include "UnitCatDlgEdit.h"


BEGIN_MESSAGE_MAP(UnitCatDlgEdit, UnitCatDlg)
END_MESSAGE_MAP()


UnitCatDlgEdit::UnitCatDlgEdit(OBJID oidCat, CWnd* pParent /*=NULL*/)
	: UnitCatDlg(oidCat, pParent)
{
	m_uTitleFormatID=IDS_TITLE_EDIT;
}

UnitCatDlgEdit::~UnitCatDlgEdit()
{
}

BOOL UnitCatDlgEdit::OnInitDialog()
{
	UnitCatDlg::OnInitDialog();

	StringA stra;
	stra.Format("call sp_unit_cat_edit(%u)", m_oid);

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
	Utf8ToWchar(row[i], len[i], pch);
	SetDlgItemText(IDC_EDT_UNIT, pch);

	return TRUE;
}

void UnitCatDlgEdit::OnOK()
{
	ValidStr cstrName;
	GetDlgItemText(IDC_EDT_NAME, cstrName);
	if(!cstrName.IsValidName())
	{
		ShowInfo(IDC_EDT_NAME, IDS_BAD_TEXT);
		return;
	}

	ValidStr cstrUnit;
	GetDlgItemText(IDC_EDT_UNIT, cstrUnit);
	if(!cstrUnit.IsValidName())
	{
		ShowInfo(IDC_EDT_UNIT, IDS_BAD_TEXT);
		return;
	}

	StringA stra;
	stra.Format("call sp_unit_cat_update(%u, '%s', '%s')", m_oid, WcharToUtf8(cstrName), WcharToUtf8(cstrUnit));

	if(!theApp.Exec(stra, this))
		return;

	m_rm.SetModified(ReloadMgr::oprEdit);

	UnitCatDlg::OnOK();
}
