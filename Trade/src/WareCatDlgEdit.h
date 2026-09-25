
#pragma once

#include "WareCatDlg.h"


class WareCatDlgEdit : public WareCatDlg
{
public:
	WareCatDlgEdit(OBJID oidCat, CWnd* pParent=NULL);
	virtual ~WareCatDlgEdit();

	virtual BOOL OnInitDialog();

protected:
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
};
