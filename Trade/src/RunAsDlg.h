
#pragma once

#include "Dialog.h"


class RunAsDlg : public Dialog
{
public:
	RunAsDlg(OBJID oidPermit, CWnd* pParent=NULL);
	virtual ~RunAsDlg();

	enum { IDD=IDD_RUN_AS };

protected:
	OBJID m_oidPermit;

	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
};
