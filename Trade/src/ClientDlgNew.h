
#pragma once

#include "ClientDlg.h"


class ClientDlgNew : public ClientDlg
{
public:
	ClientDlgNew(CWnd* pParent=NULL);
	virtual ~ClientDlgNew();

protected:
	void SetContactInfo();

	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
};
