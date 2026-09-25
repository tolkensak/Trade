
#pragma once

#include "PasswordDlg.h"


class PasswordDlgSpec : public PasswordDlg
{
public:
	PasswordDlgSpec(OBJID oidUser, CWnd* pParent=NULL);
	virtual ~PasswordDlgSpec();

	virtual BOOL OnInitDialog();

protected:
	DECLARE_MESSAGE_MAP()
};
