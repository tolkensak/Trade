
#pragma once

#include "PermitDlg.h"


class EasyPermitDlg : public PermitDlg
{
protected:
	EasyPermitDlg(OBJID oidUser, CWnd* pParent=NULL);

public:
	virtual ~EasyPermitDlg();

	enum { IDD=IDD_PERMIT_EASY };

	virtual BOOL OnInitDialog();

	afx_msg void OnLvnItemChangedList(NMHDR *pNMHDR, LRESULT *pResult);

protected:
	virtual void UpdateCheckState();

	DECLARE_MESSAGE_MAP()
};
