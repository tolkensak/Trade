
#pragma once

#include "FirmDlg.h"


class FirmDlgEdit : public FirmDlg
{
public:
	FirmDlgEdit(OBJID oidFirm, CWnd* pParent=NULL);
	virtual ~FirmDlgEdit();

	virtual BOOL OnInitDialog();

protected:
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
};
