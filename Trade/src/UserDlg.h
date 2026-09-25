
#pragma once

#include "ManipDlg.h"


class UserDlg : public ManipDlg
{
protected:
	UserDlg(OBJID oidUser, CWnd* pParent=NULL);

public:
	virtual ~UserDlg();

	enum { IDD=IDD_USER };

protected:
	virtual OBJID GetDesiredPermitID();

	DECLARE_MESSAGE_MAP()
};

inline OBJID UserDlg::GetDesiredPermitID()
{ return ID_PERMIT_EDIT_USER; }
