
#pragma once

#include "ManipDlg.h"


class PasswordDlg : public ManipDlg
{
protected:
	PasswordDlg(OBJID oidUser, CWnd* pParent=NULL);

public:
	virtual ~PasswordDlg();

	enum { IDD=IDD_PASSWORD };

protected:
	virtual OBJID GetDesiredPermitID();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
};

inline OBJID PasswordDlg::GetDesiredPermitID()
{ return ID_PERMIT_PASSWORD; }
