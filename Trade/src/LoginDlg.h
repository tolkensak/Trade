
#pragma once

#include "Dialog.h"


class LoginDlg : public Dialog
{
public:
	LoginDlg(CWnd* pParent=NULL);
	virtual ~LoginDlg();

	enum { IDD=IDD_LOGIN };

	virtual BOOL OnInitDialog();

protected:
	virtual void OnOK();

	afx_msg void OnSysCommand(UINT uID, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};
