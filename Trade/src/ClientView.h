
#pragma once

#include "ContactView.h"


class ClientView : public ContactView
{
	DECLARE_DYNCREATE(ClientView)

protected:
	ClientView();

public:
	virtual ~ClientView();

protected:
	virtual BOOL DataNew(OBJID& oid);
	virtual BOOL DataEdit(OBJID& oid);

	DECLARE_MESSAGE_MAP()
};
