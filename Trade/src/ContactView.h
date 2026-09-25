
#pragma once

#include "TableView.h"


class ContactView : public TableView
{
protected:
	ContactView(UINT uUniqueID, PCCharA pcTable);

public:
	virtual ~ContactView();

	afx_msg void OnDataContact();
	afx_msg void OnUpdateDataContact(CCmdUI *pCmdUI);

protected:
	StringA m_straTable;

	virtual BOOL ContextMenu(HMENU hMenu, UINT* puFlags, int iItem);

	DECLARE_MESSAGE_MAP()
};
