
#pragma once

#include "EasyPermitDlg.h"


class EasyPermitDlgSpec : public EasyPermitDlg
{
public:
	EasyPermitDlgSpec(OBJID oidUser, CWnd* pParent=NULL);
	virtual ~EasyPermitDlgSpec();

	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedBtnAdvanced();

protected:
	DECLARE_MESSAGE_MAP()
};
