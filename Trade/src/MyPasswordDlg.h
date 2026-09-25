
#pragma once

#include "Dialog.h"


class MyPasswordDlg : public Dialog
{
public:
	MyPasswordDlg(CWnd* pParent=NULL);
	virtual ~MyPasswordDlg();

	enum { IDD=IDD_MY_PASSWORD };

protected:
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
};
