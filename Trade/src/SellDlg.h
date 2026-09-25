
#pragma once

#include "DealDlg.h"


class SellDlg : public DealDlg
{
protected:
	SellDlg(OBJID oidSell, CWnd* pParent=NULL);

public:
	virtual ~SellDlg();

	enum { IDD=IDD_SELL };

	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedChkFreePrice();

protected:
	BOOL m_bFreePrice;

	void UpdatePriceState();
	void ChangePriceState();

	virtual OBJID GetDesiredPermitID();

	DECLARE_MESSAGE_MAP()
};

inline OBJID SellDlg::GetDesiredPermitID()
{ return ID_PERMIT_SELL; }
