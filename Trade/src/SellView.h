
#pragma once

#include "DealView.h"


class SellView : public DealView
{
	DECLARE_DYNCREATE(SellView)

protected:
	SellView();

public:
	virtual ~SellView();

	afx_msg void OnDataSellDebt();
	afx_msg void OnDataSellReturn();
	afx_msg void OnDataSubmit();

	afx_msg void OnDataStopFill();
	afx_msg void OnUpdateDataStopFill(CCmdUI *pCmdUI);
	afx_msg void OnDataView();
	afx_msg void OnUpdateDataView(CCmdUI *pCmdUI);
	afx_msg void OnDataExport();
	afx_msg void OnUpdateDataExport(CCmdUI *pCmdUI);

	afx_msg LRESULT OnViewActivated(WPARAM wp, LPARAM lp);
	afx_msg LRESULT OnUmUpdateUI(WPARAM wp, LPARAM lp);

protected:
	void SetTitle(BOOL bSet=TRUE);

	virtual BOOL DataNew(OBJID& oid);
	virtual BOOL DataEdit(OBJID& oid);

	DECLARE_MESSAGE_MAP()
};
