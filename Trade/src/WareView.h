
#pragma once

#include "TableView.h"


class WareView : public TableView
{
	DECLARE_DYNCREATE(WareView)

protected:
	WareView();

public:
	virtual ~WareView();

	afx_msg void OnDataPrice();
	afx_msg void OnUpdateDataPrice(CCmdUI *pCmdUI);

protected:
	virtual BOOL ContextMenu(HMENU hMenu, UINT* puFlags, int iItem);
	virtual BOOL DataNew(OBJID& oid);
	virtual BOOL DataEdit(OBJID& oid);

	DECLARE_MESSAGE_MAP()
};
