
#pragma once

#include "GridDlg.h"


class DebtDlg : public GridDlg
{
protected:
	DebtDlg(PCCharA pcaTable, CWnd* pParent=NULL);

public:
	virtual ~DebtDlg();

	enum { IDD=IDD_DEBT };

protected:
	DECLARE_MESSAGE_MAP()
};
