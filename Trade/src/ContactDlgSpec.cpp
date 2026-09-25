
#include "stdafx.h"
#include "App.h"
#include "ContactDlgSpec.h"


BEGIN_MESSAGE_MAP(ContactDlgSpec, ContactDlg)
END_MESSAGE_MAP()


ContactDlgSpec::ContactDlgSpec(OBJID oidContact, CWnd* pParent /*=NULL*/)
	: ContactDlg(oidContact, pParent)
{
}

ContactDlgSpec::~ContactDlgSpec()
{
}

BOOL ContactDlgSpec::OnInitDialog()
{
	ContactDlg::OnInitDialog();

	StringA stra;
	stra.Format("call sp_contact_edit(%u)", m_oid);

	MySQLResPtr pRes=theApp.Query(stra, this);
	if(!pRes)
		return TRUE;

	MYSQL_ROW row=pRes->FetchRow();
	if(!row)
		return TRUE;

	TCHAR pch[TOL_MAXSTR];
	PULONG len=pRes->FetchLengths();

	m_pDataOrg=new Data;

	int i=0; // fname
	Utf8ToWchar(row[i], len[i], pch);
	SetDlgItemText(IDC_EDT_FIRST_NAME, pch);
	m_pDataOrg->cstrFirstName=pch;

	i++; // lname
	Utf8ToWchar(row[i], len[i], pch);
	SetDlgItemText(IDC_EDT_LAST_NAME, pch);
	m_pDataOrg->cstrLastName=pch;

	i++; // phone
	Utf8ToWchar(row[i], len[i], pch);
	SetDlgItemText(IDC_EDT_PHONE, pch);
	m_pDataOrg->cstrPhone=pch;

	i++; // mobile
	Utf8ToWchar(row[i], len[i], pch);
	SetDlgItemText(IDC_EDT_MOBILE, pch);
	m_pDataOrg->cstrMobile=pch;

	i++; // address
	Utf8ToWchar(row[i], len[i], pch);
	SetDlgItemText(IDC_EDT_ADDRESS, pch);
	m_pDataOrg->cstrAddress=pch;

	i++; // comment
	Utf8ToWchar(row[i], len[i], pch);
	SetDlgItemText(IDC_EDT_COMMENT, pch);
	m_pDataOrg->cstrComment=pch;

	return TRUE;
}

void ContactDlgSpec::OnOK()
{
	Data data;
	if(!PrepareData(data))
		return;

	if(!m_pDataOrg)
		return;

	if(*m_pDataOrg==data)
	{
		ContactDlg::OnCancel();
		return;
	}

	StringA stra;
	stra.Format("update contact \
					set first_name='%s' \
						, last_name='%s' \
						, phone='%s' \
						, mobile='%s' \
						, address='%s' \
						, comment='%s' \
					where id=%u"
					, WcharToUtf8(data.cstrFirstName)
					, WcharToUtf8(data.cstrLastName)
					, WcharToUtf8(data.cstrPhone)
					, WcharToUtf8(data.cstrMobile)
					, WcharToUtf8(data.cstrAddress)
					, WcharToUtf8(data.cstrComment)
					, m_oid);

	if(!theApp.Exec(stra, this))
		return;

	m_rm.SetModified(ReloadMgr::oprEdit);

	ContactDlg::OnOK();
}
