
#include "stdafx.h"
#include "App.h"
#include "WareDlgEdit.h"


BEGIN_MESSAGE_MAP(WareDlgEdit, WareDlg)
END_MESSAGE_MAP()


WareDlgEdit::WareDlgEdit(OBJID oidWare, CWnd* pParent /*=NULL*/)
	: WareDlg(oidWare, pParent)
{
	m_uTitleFormatID=IDS_TITLE_EDIT;
}

WareDlgEdit::~WareDlgEdit()
{
}

void WareDlgEdit::ReloadCmbFirm()
{
	CbReload(IDC_CMB_FIRM, "select id, name from firm order by name", -1, m_oidFirm);
}

BOOL WareDlgEdit::OnInitDialog()
{
	StringA stra;
	stra.Format("call sp_ware_edit(%u)", m_oid);

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
	m_oidWareCat=atoi(row[i]);

	i++;
	m_oidUnitCat=atoi(row[i]);

	i++;
	m_oidFirm=atoi(row[i]);

	WareDlg::OnInitDialog();
	return TRUE;
}

void WareDlgEdit::OnOK()
{
	ValidStr cstrName;
	if(!IsValid(cstrName))
		return;

	StringA stra;
	stra.Format("update ware set name='%s', wcid=%u, ucid=%u, fid=%u where id=%u"
		, WcharToUtf8(cstrName)
		, m_oidWareCat
		, m_oidUnitCat
		, m_oidFirm
		, m_oid);

	if(!theApp.Exec(stra, this))
		return;

	m_rm.SetModified(ReloadMgr::oprEdit);

	WareDlg::OnOK();
}
