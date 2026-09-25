
#pragma once

#include "ManipDlg.h"


class FirmDlg : public ManipDlg
{
protected:
	FirmDlg(OBJID oidFirm, CWnd* pParent=NULL);

public:
	virtual ~FirmDlg();

	enum { IDD=IDD_FIRM };

protected:
	virtual OBJID GetDesiredPermitID();

	DECLARE_MESSAGE_MAP()
};

inline OBJID FirmDlg::GetDesiredPermitID()
{ return ID_PERMIT_EDIT_FIRM; }
