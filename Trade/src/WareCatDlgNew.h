
#pragma once

#include "WareCatDlg.h"


class WareCatDlgNew : public WareCatDlg
{
public:
	WareCatDlgNew(CWnd* pParent=NULL);
	virtual ~WareCatDlgNew();

protected:
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
};
