
#pragma once

#include "AdvancedPermitDlg.h"


class AdvancedPermitDlgGlob : public AdvancedPermitDlg
{
public:
	AdvancedPermitDlgGlob(CWnd* pParent=NULL);
	virtual ~AdvancedPermitDlgGlob();

	virtual BOOL OnInitDialog();

	afx_msg void OnCbnSelChangeCmbUser();

protected:
	DECLARE_MESSAGE_MAP()
};
