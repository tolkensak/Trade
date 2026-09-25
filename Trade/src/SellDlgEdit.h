
#pragma once

#include "SellDlg.h"


class SellDlgEdit : public SellDlg
{
public:
	SellDlgEdit(OBJID oidSell, CWnd* pParent=NULL);
	virtual ~SellDlgEdit();

	virtual BOOL OnInitDialog();

protected:
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
};
