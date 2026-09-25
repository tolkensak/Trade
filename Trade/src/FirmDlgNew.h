
#pragma once

#include "FirmDlg.h"


class FirmDlgNew : public FirmDlg
{
public:
	FirmDlgNew(CWnd* pParent=NULL);
	virtual ~FirmDlgNew();

protected:
	void SetContactInfo();

	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
};
