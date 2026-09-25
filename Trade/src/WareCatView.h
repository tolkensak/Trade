
#pragma once

#include "TableView.h"


class WareCatView : public TableView
{
	DECLARE_DYNCREATE(WareCatView)

protected:
	WareCatView();

public:
	virtual ~WareCatView();

protected:
	virtual BOOL DataNew(OBJID& oid);
	virtual BOOL DataEdit(OBJID& oid);

	DECLARE_MESSAGE_MAP()
};
