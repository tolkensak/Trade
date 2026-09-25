
#pragma once

#include "WareDlg.h"


class WareDlgNew : public WareDlg
{
public:
	WareDlgNew(CWnd* pParent=NULL);
	virtual ~WareDlgNew();

protected:
	virtual void ReloadCmbFirm();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
};
