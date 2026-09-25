
#pragma once

#include "UserDlg.h"


class UserDlgNew : public UserDlg
{
public:
	UserDlgNew(CWnd* pParent=NULL);
	virtual ~UserDlgNew();

protected:
	void SetContactInfo();

	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
};
