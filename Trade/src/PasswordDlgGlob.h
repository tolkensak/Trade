
#pragma once

#include "PasswordDlg.h"


class PasswordDlgGlob : public PasswordDlg
{
public:
	PasswordDlgGlob(CWnd* pParent=NULL);
	virtual ~PasswordDlgGlob();

	virtual BOOL OnInitDialog();

	afx_msg void OnCbnSelChangeCmbUser();

protected:
	DECLARE_MESSAGE_MAP()
};
