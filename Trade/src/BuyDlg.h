
#pragma once

#include "DealDlg.h"


class BuyDlg : public DealDlg
{
protected:
	BuyDlg(OBJID oidBuy, CWnd* pParent=NULL);

public:
	virtual ~BuyDlg();

	enum { IDD=IDD_BUY };

protected:
	virtual OBJID GetDesiredPermitID();

	DECLARE_MESSAGE_MAP()
};

inline OBJID BuyDlg::GetDesiredPermitID()
{ return ID_PERMIT_BUY; }
