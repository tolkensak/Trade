
#pragma once

#include "ContactView.h"


class FirmView : public ContactView
{
	DECLARE_DYNCREATE(FirmView)

protected:
	FirmView();

public:
	virtual ~FirmView();

protected:
	virtual BOOL DataNew(OBJID& oid);
	virtual BOOL DataEdit(OBJID& oid);

	DECLARE_MESSAGE_MAP()
};
