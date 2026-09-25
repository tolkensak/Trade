
#pragma once

#include "DealView.h"


class BuyView : public DealView
{
	DECLARE_DYNCREATE(BuyView)

protected:
	BuyView();

public:
	virtual ~BuyView();

	afx_msg void OnDataBuyDebt();
	afx_msg void OnDataBuyReturn();

protected:
	virtual BOOL DataNew(OBJID& oid);
	virtual BOOL DataEdit(OBJID& oid);

	DECLARE_MESSAGE_MAP()
};
