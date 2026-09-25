
#pragma once

#include "EasyPermitDlg.h"


class EasyPermitDlgGlob : public EasyPermitDlg
{
public:
	EasyPermitDlgGlob(CWnd* pParent=NULL);
	virtual ~EasyPermitDlgGlob();

	virtual BOOL OnInitDialog();

	afx_msg void OnCbnSelChangeCmbUser();
	afx_msg void OnBnClickedBtnAdvanced();

protected:
	DECLARE_MESSAGE_MAP()
};
