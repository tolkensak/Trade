
#pragma once

#include "TableView.h"


class UnitCatView : public TableView
{
	DECLARE_DYNCREATE(UnitCatView)

protected:
	UnitCatView();

public:
	virtual ~UnitCatView();

protected:
	virtual BOOL DataNew(OBJID& oid);
	virtual BOOL DataEdit(OBJID& oid);

	DECLARE_MESSAGE_MAP()
};
