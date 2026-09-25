
#pragma once

#include "ManipDlg.h"


class WareCatDlg : public ManipDlg
{
protected:
	WareCatDlg(OBJID oidCat, CWnd* pParent=NULL);

public:
	virtual ~WareCatDlg();

	enum { IDD=IDD_WARE_CAT };

protected:
	virtual OBJID GetDesiredPermitID();

	DECLARE_MESSAGE_MAP()
};

inline OBJID WareCatDlg::GetDesiredPermitID()
{ return ID_PERMIT_EDIT_WARE; }
