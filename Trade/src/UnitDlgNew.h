
#pragma once

#include "UnitDlg.h"


class UnitDlgNew : public UnitDlg
{
public:
	UnitDlgNew(CWnd* pParent=NULL);
	virtual ~UnitDlgNew();

	virtual BOOL OnInitDialog();

	afx_msg void OnCbnSelChangeCmbCat();
	afx_msg void OnBnClickedBtnCat();

protected:
	void ReloadCmbCat();

	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
};
