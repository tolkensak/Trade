
#include "stdafx.h"
#include "App.h"
#include "FirmDlgNew.h"
#include "ContactDlgSpec.h"


BEGIN_MESSAGE_MAP(FirmDlgNew, FirmDlg)
END_MESSAGE_MAP()


FirmDlgNew::FirmDlgNew(CWnd* pParent /*=NULL*/)
	: FirmDlg(0, pParent)
{
	m_uTitleFormatID=IDS_TITLE_NEW;
}

FirmDlgNew::~FirmDlgNew()
{
}

void FirmDlgNew::OnOK()
{
	ValidStr cstrName;
	GetDlgItemText(IDC_EDT_NAME, cstrName);
	if(!cstrName.IsValidName())
	{
		ShowInfo(IDC_EDT_NAME, IDS_BAD_TEXT);
		return;
	}

	StringA stra;
	stra.Format("insert into firm(name, disabled, uid) values('%s', %u, %u)"
		, WcharToUtf8(cstrName)
		, IsDlgButtonChecked(IDC_CHK_DISABLED)
		, theApp.GetUser().GetID());

	m_oid=theApp.Insert(stra, this);
	if(m_oid==0)
		return;

	if(MsgBox(this, MB_YESNO|MB_ICONQUESTION, IDS_PROMPT_CONTACT_INFO, cstrName)==IDYES)
		SetContactInfo();

	m_rm.SetModified(ReloadMgr::oprNew);

	FirmDlg::OnOK();
}

void FirmDlgNew::SetContactInfo()
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
