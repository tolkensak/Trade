
#pragma once

#include "SellDlg.h"


class SellDlgNew : public SellDlg
{
public:
	SellDlgNew(OBJID oidLot, CWnd* pParent=NULL);
	virtual ~SellDlgNew();

protected:
	OBJID m_oidLot;

	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
};
