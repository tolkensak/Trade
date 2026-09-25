
#pragma once

#include "IndentDlg.h"


class IndentDlgNew : public IndentDlg
{
public:
	IndentDlgNew(CWnd* pParent=NULL);
	virtual ~IndentDlgNew();

protected:
	virtual void ReloadCmbClient();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
};
