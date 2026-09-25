
#pragma once

#include "PermitDlg.h"


class AdvancedPermitDlg : public PermitDlg
{
protected:
	AdvancedPermitDlg(OBJID oidUser, CWnd* pParent=NULL);

public:
	virtual ~AdvancedPermitDlg();

	enum { IDD=IDD_PERMIT_ADVANCED };

	virtual BOOL OnInitDialog();

	afx_msg void OnLvnItemChangedList(NMHDR *pNMHDR, LRESULT *pResult);

protected:
	virtual void UpdateCheckState();

	DECLARE_MESSAGE_MAP()
};
