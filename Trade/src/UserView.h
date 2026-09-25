
#pragma once

#include "ContactView.h"


class UserView : public ContactView
{
	DECLARE_DYNCREATE(UserView)

protected:
	UserView();

public:
	virtual ~UserView();

	afx_msg void OnDataPermit();
	afx_msg void OnDataPassword();
	afx_msg void OnUpdateDataPermit(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDataPassword(CCmdUI *pCmdUI);

protected:
	virtual BOOL ContextMenu(HMENU hMenu, UINT* puFlags, int iItem);
	virtual BOOL DataNew(OBJID& oid);
	virtual BOOL DataEdit(OBJID& oid);

	DECLARE_MESSAGE_MAP()
};
