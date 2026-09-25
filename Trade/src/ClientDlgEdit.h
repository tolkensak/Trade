
#pragma once

#include "ClientDlg.h"


class ClientDlgEdit : public ClientDlg
{
public:
	ClientDlgEdit(OBJID oidClient, CWnd* pParent=NULL);
	virtual ~ClientDlgEdit();

	virtual BOOL OnInitDialog();

protected:
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
};
