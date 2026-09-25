
#pragma once

#include "WareDlg.h"


class WareDlgEdit : public WareDlg
{
public:
	WareDlgEdit(OBJID oidWare, CWnd* pParent=NULL);
	virtual ~WareDlgEdit();

	virtual BOOL OnInitDialog();

protected:
	virtual void ReloadCmbFirm();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
};
