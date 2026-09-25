
#pragma once

#include "ContactDlg.h"


class ContactDlgGlob : public ContactDlg
{
public:
	ContactDlgGlob(CWnd* pParent=NULL);
	virtual ~ContactDlgGlob();

protected:
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
};
