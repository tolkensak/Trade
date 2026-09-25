
#pragma once

#include "BuyDlg.h"


class BuyDlgEdit : public BuyDlg
{
public:
	BuyDlgEdit(OBJID oidBuy, CWnd* pParent=NULL);
	virtual ~BuyDlgEdit();

	virtual BOOL OnInitDialog();

protected:
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
};
