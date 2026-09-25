
#pragma once

#include "IndentDlg.h"


class IndentDlgEdit : public IndentDlg
{
public:
	IndentDlgEdit(OBJID oidLot, CWnd* pParent=NULL);
	virtual ~IndentDlgEdit();

	virtual BOOL OnInitDialog();

protected:
	virtual void ReloadCmbClient();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
};
