
#pragma once

#include "UnitDlg.h"


class UnitDlgEdit : public UnitDlg
{
public:
	UnitDlgEdit(OBJID oidUnit, CWnd* pParent=NULL);
	virtual ~UnitDlgEdit();

	virtual BOOL OnInitDialog();

protected:
	BOOL m_bMainUnit;

	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
};
