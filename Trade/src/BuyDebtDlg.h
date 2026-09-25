
#pragma once

#include "DebtDlg.h"


class BuyDebtDlg : public DebtDlg
{
public:
	BuyDebtDlg(CWnd* pParent=NULL);
	virtual ~BuyDebtDlg();

protected:
	virtual OBJID GetDesiredPermitID();

	DECLARE_MESSAGE_MAP()
};

inline OBJID BuyDebtDlg::GetDesiredPermitID()
{ return ID_PERMIT_BUY_DEBT; }
