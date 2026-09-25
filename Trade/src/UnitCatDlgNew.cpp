
#include "stdafx.h"
#include "App.h"
#include "UnitCatDlgNew.h"


BEGIN_MESSAGE_MAP(UnitCatDlgNew, UnitCatDlg)
END_MESSAGE_MAP()


UnitCatDlgNew::UnitCatDlgNew(CWnd* pParent /*=NULL*/)
	: UnitCatDlg(0, pParent)
{
	m_uTitleFormatID=IDS_TITLE_NEW;
}

UnitCatDlgNew::~UnitCatDlgNew()
{
}

void UnitCatDlgNew::OnOK()
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
	stra.Format("call sp_unit_cat_insert('%s', '%s')", WcharToUtf8(cstrName), WcharToUtf8(cstrUnit));

	MySQLResPtr pRes=theApp.Query(stra, this);
	if(!pRes)
		return;

	MYSQL_ROW row=pRes->FetchRow();
	if(!row)
		return;

	m_oid=atoi(row[0]);
	if(m_oid==0)
		return;

	m_rm.SetModified(ReloadMgr::oprNew);

	UnitCatDlg::OnOK();
}
