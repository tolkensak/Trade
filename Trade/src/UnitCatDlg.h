
#pragma once

#include "ManipDlg.h"


class UnitCatDlg : public ManipDlg
{
protected:
	UnitCatDlg(OBJID oidCat, CWnd* pParent=NULL);

public:
	virtual ~UnitCatDlg();

	enum { IDD=IDD_UNIT_CAT };

protected:
	virtual OBJID GetDesiredPermitID();

	DECLARE_MESSAGE_MAP()
};

inline OBJID UnitCatDlg::GetDesiredPermitID()
{ return ID_PERMIT_EDIT_UNIT; }
