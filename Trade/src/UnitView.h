
#pragma once

#include "TableView.h"


class UnitView : public TableView
{
	DECLARE_DYNCREATE(UnitView)

protected:
	UnitView();

public:
	virtual ~UnitView();

protected:
	virtual BOOL DataNew(OBJID& oid);
	virtual BOOL DataEdit(OBJID& oid);

	DECLARE_MESSAGE_MAP()
};
