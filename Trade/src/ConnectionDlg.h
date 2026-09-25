
#pragma once

#include "Dialog.h"


class ConnectionDlg : public Dialog
{
public:
	ConnectionDlg(CWnd* pParent=NULL);
	virtual ~ConnectionDlg();

	enum { IDD=IDD_CONNECTION };

	static void GetHost(StringW& strw);
	static void GetHost(StringA& stra);
	static void GetHost(CString& cstr);

	virtual BOOL OnInitDialog();

protected:
	CString m_strHostOrg;

	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
};
