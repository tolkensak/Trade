
#pragma once

#include "UserDlg.h"


class UserDlgEdit : public UserDlg
{
public:
	UserDlgEdit(OBJID oidUser, CWnd* pParent=NULL);
	virtual ~UserDlgEdit();

	virtual BOOL OnInitDialog();

protected:
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
};
