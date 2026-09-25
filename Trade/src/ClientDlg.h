
#pragma once

#include "ManipDlg.h"


class ClientDlg : public ManipDlg
{
protected:
	ClientDlg(OBJID oidClient, CWnd* pParent=NULL);

public:
	virtual ~ClientDlg();

	enum { IDD=IDD_CLIENT };

protected:
	virtual OBJID GetDesiredPermitID();

	DECLARE_MESSAGE_MAP()
};

inline OBJID ClientDlg::GetDesiredPermitID()
{ return ID_PERMIT_EDIT_CLIENT; }
