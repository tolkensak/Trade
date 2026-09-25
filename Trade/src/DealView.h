
#pragma once

#include "TableView.h"


class DealView : public TableView
{
protected:
	DealView(UINT uUniqueID, PCCharA pcTablePrefix);

public:
	virtual ~DealView();

	virtual void OnInitialUpdate();

	afx_msg void OnDataSubmit();
	afx_msg void OnUpdateDataSubmit(CCmdUI *pCmdUI);

protected:
	OBJID m_oidLot;
	StringA m_straTablePrefix;

	void ChangeLot(OBJID oidLot);
	void ReloadLot(OBJID oidDeal=0);

	virtual BOOL ContextMenu(HMENU hMenu, UINT* puFlags, int iItem);
	virtual BOOL GetSum(double& dSum) const;

	DECLARE_MESSAGE_MAP()
};
