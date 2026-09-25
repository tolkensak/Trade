
#include "stdafx.h"
#include "App.h"
#include "ContactDlg.h"


ContactDlg::Data::Data()
{
}

ContactDlg::Data::~Data()
{
}

//void ContactDlg::Data::PrepareForDB(Data& data) const
//{
//	cstrFirstName.GetDBStr(data.cstrFirstName);
//	cstrLastName.GetDBStr(data.cstrLastName);
//	cstrMobile.GetDBStr(data.cstrMobile);
//	cstrPhone.GetDBStr(data.cstrPhone);
//	cstrAddress.GetDBStr(data.cstrAddress);
//}

BOOL operator==(const ContactDlg::Data& data1, const ContactDlg::Data& data2)
{
	return data1.cstrFirstName==data2.cstrFirstName
		&& data1.cstrLastName==data2.cstrLastName
		&& data1.cstrMobile==data2.cstrMobile
		&& data1.cstrPhone==data2.cstrPhone
		&& data1.cstrAddress==data2.cstrAddress
		&& data1.cstrComment==data2.cstrComment;
}


BEGIN_MESSAGE_MAP(ContactDlg, ManipDlg)
END_MESSAGE_MAP()


ContactDlg::ContactDlg(OBJID oidContact, CWnd* pParent /*=NULL*/)
	: ManipDlg(ContactDlg::IDD, oidContact, pParent)
{
	m_rm.SetObject(ReloadMgr::objContact);
}

ContactDlg::~ContactDlg()
{
}

BOOL ContactDlg::PrepareData(Data& data)
{
	GetDlgItemText(IDC_EDT_FIRST_NAME, data.cstrFirstName);
	if(!data.cstrFirstName.IsEmpty() && !data.cstrFirstName.IsValidName())
	{
		ShowInfo(IDC_EDT_FIRST_NAME, IDS_BAD_TEXT);
		return FALSE;
	}

	GetDlgItemText(IDC_EDT_LAST_NAME, data.cstrLastName);
	if(!data.cstrLastName.IsEmpty() && !data.cstrLastName.IsValidName())
	{
		ShowInfo(IDC_EDT_LAST_NAME, IDS_BAD_TEXT);
		return FALSE;
	}

	GetDlgItemText(IDC_EDT_PHONE, data.cstrPhone);
	data.cstrPhone.Trim();

	GetDlgItemText(IDC_EDT_MOBILE, data.cstrMobile);
	data.cstrMobile.Trim();

	GetDlgItemText(IDC_EDT_ADDRESS, data.cstrAddress);
	data.cstrAddress.Trim();

	GetDlgItemText(IDC_EDT_COMMENT, data.cstrComment);
	data.cstrComment.Trim();

	return TRUE;
}
