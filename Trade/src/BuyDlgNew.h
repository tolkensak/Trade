
#pragma once

#include "BuyDlg.h"


class BuyDlgNew : public BuyDlg
{
public:
	BuyDlgNew(OBJID oidLot, CWnd* pParent=NULL);
	virtual ~BuyDlgNew();

protected:
	OBJID m_oidLot;

	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
};
