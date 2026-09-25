
#pragma once

#include "DebtDlg.h"


class SellDebtDlg : public DebtDlg
{
public:
	SellDebtDlg(CWnd* pParent=NULL);
	virtual ~SellDebtDlg();

protected:
	virtual OBJID GetDesiredPermitID();

	DECLARE_MESSAGE_MAP()
};

inline OBJID SellDebtDlg::GetDesiredPermitID()
{ return ID_PERMIT_SELL_DEBT; }
