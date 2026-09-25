
#include "stdafx.h"
#include "App.h"
#include "UnitDlgEdit.h"


BEGIN_MESSAGE_MAP(UnitDlgEdit, UnitDlg)
END_MESSAGE_MAP()


UnitDlgEdit::UnitDlgEdit(OBJID oidUnit, CWnd* pParent /*=NULL*/)
	: UnitDlg(oidUnit, pParent)
{
	m_uTitleFormatID=IDS_TITLE_EDIT;
}

UnitDlgEdit::~UnitDlgEdit()
{
}

BOOL UnitDlgEdit::OnInitDialog()
{
	UnitDlg::OnInitDialog();

	GetDlgItem(IDC_CMB_CAT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_CAT)->EnableWindow(FALSE);

	StringA stra;
	stra.Format("call sp_unit_edit(%u)", m_oid);

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
	m_oidCat=atoi(row[i]);

	i++;
	Utf8ToWchar(row[i], len[i], pch);
	SetDlgItemText(IDC_EDT_RATIO, pch);

	stra.Format("select id, name from unit_cat where id=%u", m_oidCat);
	CbReload(IDC_CMB_CAT, stra, 0);
	ReloadCmbUnit();

	return TRUE;
}

void UnitDlgEdit::OnOK()
{
	ValidStr cstrName;
	GetDlgItemText(IDC_EDT_NAME, cstrName);
	if(!cstrName.IsValidName())
	{
		ShowInfo(IDC_EDT_NAME, IDS_BAD_TEXT);
		return;
	}

	ValidStr cstrRatio;
	GetDlgItemText(IDC_EDT_RATIO, cstrRatio);
	if(!cstrRatio.IsValidNumber() || _tstof(cstrRatio)==0)
	{
		ShowInfo(IDC_EDT_RATIO, IDS_BAD_TEXT);
		return;
	}

	OBJID oidUnitRatio=CbGetOid(IDC_CMB_UNIT);
	if(oidUnitRatio==0)
	{
		ShowInfo(IDC_CMB_UNIT, IDS_BAD_SELECT);
		return;
	}

	StringA stra;
	stra.Format("update unit set name='%s', ratio=(%s)*(%f) where id=%u"
		, WcharToUtf8(cstrName)
		, WcharToUtf8(cstrRatio)
		, GetUnitRatio(oidUnitRatio)
		, m_oid);

	if(!theApp.Exec(stra, this))
		return;

	m_rm.SetModified(ReloadMgr::oprEdit);

	UnitDlg::OnOK();
}
