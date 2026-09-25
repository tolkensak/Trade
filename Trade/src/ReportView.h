
#pragma once

#include "TableView.h"


class ReportView : public TableView
{
	DECLARE_DYNCREATE(ReportView)

protected:
	ReportView();

public:
	virtual ~ReportView();

	afx_msg void OnDataEdit();
	afx_msg void OnDataView();
	afx_msg void OnDataExport();
	afx_msg void OnUpdateDataView(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDataExport(CCmdUI *pCmdUI);

	afx_msg void OnDataNew();
	afx_msg void OnDataDelete();
	afx_msg void OnUpdateDataDelete(CCmdUI *pCmdUI);

protected:
	void MakeReport(OBJID oidReport);

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL ContextMenu(HMENU hMenu, UINT* puFlags, int iItem);
	virtual void DblClkItem(int nItem);
	virtual void Reload();

	DECLARE_MESSAGE_MAP()
};
