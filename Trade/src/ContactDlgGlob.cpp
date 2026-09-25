
#include "stdafx.h"
#include "App.h"
#include "ContactDlgGlob.h"


BEGIN_MESSAGE_MAP(ContactDlgGlob, ContactDlg)
END_MESSAGE_MAP()


ContactDlgGlob::ContactDlgGlob(CWnd* pParent /*=NULL*/)
	: ContactDlg(0, pParent)
{
}

ContactDlgGlob::~ContactDlgGlob()
{
}

void ContactDlgGlob::OnOK()
{
	Data data;
	if(!PrepareData(data))
		return;

	StringA stra;
	stra.Format("insert into contact(first_name, last_name, phone, mobile, address, comment) \
				values('%s', '%s', '%s', '%s', '%s', '%s')"
					, WcharToUtf8(data.cstrFirstName)
					, WcharToUtf8(data.cstrLastName)
					, WcharToUtf8(data.cstrPhone)
					, WcharToUtf8(data.cstrMobile)
					, WcharToUtf8(data.cstrAddress)
					, WcharToUtf8(data.cstrComment));

	m_oid=theApp.Insert(stra, this);
	if(m_oid==0)
		return;

	m_rm.SetModified(ReloadMgr::oprNew);

	ContactDlg::OnOK();
}
