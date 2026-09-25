
#pragma once

#include "Column.h"


class GridView : public CListView
{
protected:
	GridView(UINT uUniqueID=0); // uUniqueID aimed for RestoreColumn & StoreColumn. They will do nothing if it zero

public:
	virtual ~GridView();

	UINT GetUniqueID() const;

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint point);
	afx_msg void OnHdnEndDrag(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnColumn(UINT uCmdID);
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
	//afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg LRESULT OnUmUpdateUI(WPARAM wp, LPARAM lp);

	CString GetEmptyMessage() const;
	void GetEmptyMessage(CString& str) const;
	void SetEmptyMessage(LPCTSTR pc=NULL);
	void SetEmptyMessage(UINT uResID);

protected:
	UINT m_uUniqueID; // RestoreColumn & StoreColumn will do nothing if it equal to zero
	ColumnArray m_arrColumn;
	CString m_strEmptyMessage;

	BOOL LayColumn();

	void RestoreColumn();
	void StoreColumn();

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void ContextMenuHeader(CPoint pt);
	virtual BOOL ContextMenuClient(HMENU hMenu, UINT* puFlags, int iItem);
	virtual void DblClkItem(int nItem);

	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()
};

inline UINT GridView::GetUniqueID() const
{ return m_uUniqueID; }

inline CString GridView::GetEmptyMessage() const
{ return m_strEmptyMessage; }

inline void GridView::GetEmptyMessage(CString& str) const
{ str=m_strEmptyMessage; }
