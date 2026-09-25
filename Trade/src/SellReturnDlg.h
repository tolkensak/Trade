
#pragma once

#include "ReturnDlg.h"


class SellReturnDlg : public ReturnDlg
{
public:
	SellReturnDlg(CWnd* pParent=NULL);
	virtual ~SellReturnDlg();

protected:
	virtual OBJID GetDesiredPermitID();

	DECLARE_MESSAGE_MAP()
};

inline OBJID SellReturnDlg::GetDesiredPermitID()
{ return ID_PERMIT_SELL_RETURN; }
