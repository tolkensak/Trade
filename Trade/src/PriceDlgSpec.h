
#pragma once

#include "PriceDlg.h"


class PriceDlgSpec : public PriceDlg
{
public:
	PriceDlgSpec(OBJID oidWare, CWnd* pParent=NULL);
	virtual ~PriceDlgSpec();

	virtual BOOL OnInitDialog();

protected:
	DECLARE_MESSAGE_MAP()
};
