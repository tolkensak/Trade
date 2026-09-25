
#pragma once

#include "UnitCatDlg.h"


class UnitCatDlgEdit : public UnitCatDlg
{
public:
	UnitCatDlgEdit(OBJID oidCat, CWnd* pParent=NULL);
	virtual ~UnitCatDlgEdit();

	virtual BOOL OnInitDialog();

protected:
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
};
