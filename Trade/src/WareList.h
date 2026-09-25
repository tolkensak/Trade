
#pragma once

#include "Column.h"


class WareList : public CListCtrl
{
public:
	WareList();
	virtual ~WareList();

	void Reload(const CString& strPrefix);

	//afx_msg int OnCreate(LPCREATESTRUCT pcs);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

protected:
	ColumnArray m_arrColumn;

	BOOL LayColumn();

	virtual void PreSubclassWindow();
	//virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	DECLARE_MESSAGE_MAP()
};
