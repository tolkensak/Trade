
#pragma once

#include "ContactDlg.h"


class ContactDlgSpec : public ContactDlg
{
public:
	ContactDlgSpec(OBJID oidContact, CWnd* pParent=NULL);
	virtual ~ContactDlgSpec();

	virtual BOOL OnInitDialog();

protected:
	SmartPointer<Data> m_pDataOrg;

	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
};
