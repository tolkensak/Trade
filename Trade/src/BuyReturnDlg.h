
#pragma once

#include "ReturnDlg.h"


class BuyReturnDlg : public ReturnDlg
{
public:
	BuyReturnDlg(CWnd* pParent=NULL);
	virtual ~BuyReturnDlg();

protected:
	virtual OBJID GetDesiredPermitID();

	DECLARE_MESSAGE_MAP()
};

inline OBJID BuyReturnDlg::GetDesiredPermitID()
{ return ID_PERMIT_BUY_RETURN; }
