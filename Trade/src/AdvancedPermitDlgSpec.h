
#pragma once

#include "AdvancedPermitDlg.h"


class AdvancedPermitDlgSpec : public AdvancedPermitDlg
{
public:
	AdvancedPermitDlgSpec(OBJID oidUser, CWnd* pParent=NULL);
	virtual ~AdvancedPermitDlgSpec();

	virtual BOOL OnInitDialog();

protected:
	DECLARE_MESSAGE_MAP()
};
