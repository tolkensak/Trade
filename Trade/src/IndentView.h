
#pragma once

#include "TableView.h"


class IndentView : public TableView
{
	DECLARE_DYNCREATE(IndentView)

protected:
	IndentView();

public:
	virtual ~IndentView();

	afx_msg void OnDataFill();
	afx_msg void OnUpdateDataFill(CCmdUI *pCmdUI);
	afx_msg void OnDataSubmit();
	afx_msg void OnUpdateDataSubmit(CCmdUI *pCmdUI);
	afx_msg void OnDataView();
	afx_msg void OnUpdateDataView(CCmdUI *pCmdUI);
	afx_msg void OnDataExport();
	afx_msg void OnUpdateDataExport(CCmdUI *pCmdUI);

protected:
	BOOL DataSubmit(int* pnSubmit, int nCount);

	virtual BOOL ContextMenu(HMENU hMenu, UINT* puFlags, int iItem);
	virtual BOOL DataNew(OBJID& oid);
	virtual BOOL DataEdit(OBJID& oid);

	DECLARE_MESSAGE_MAP()
};
