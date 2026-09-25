
#pragma once

#include "UnitCatDlg.h"


class UnitCatDlgNew : public UnitCatDlg
{
public:
	UnitCatDlgNew(CWnd* pParent=NULL);
	virtual ~UnitCatDlgNew();

protected:
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
};
