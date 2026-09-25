
#pragma once

#include "ManipDlg.h"


class UnitDlg : public ManipDlg
{
protected:
	UnitDlg(OBJID oidUnit, CWnd* pParent=NULL);

public:
	virtual ~UnitDlg();

	enum { IDD=IDD_UNIT };

protected:
	OBJID m_oidCat;

	void ReloadCmbUnit();

	virtual OBJID GetDesiredPermitID();

	DECLARE_MESSAGE_MAP()
};

inline OBJID UnitDlg::GetDesiredPermitID()
{ return ID_PERMIT_EDIT_UNIT; }
