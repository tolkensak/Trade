
#pragma once

#include "GridView.h"
#include "ReloadMgr.h"


class TableView : public GridView
{
protected:
	TableView(UINT uUniqueID);

public:
	virtual ~TableView();

	afx_msg LRESULT OnViewActivated(WPARAM, LPARAM);
	afx_msg void OnViewReload();
	afx_msg void OnDataNew();
	afx_msg void OnDataEdit();
	afx_msg void OnDataDelete();
	afx_msg void OnUpdateDataEdit(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDataDelete(CCmdUI *pCmdUI);
	afx_msg LRESULT OnUmUpdateUI(WPARAM wp, LPARAM lp);

private:
	BOOL m_bFirstTimeActivated;

protected:
	ReloadMgr m_rm;

	StringA m_straReload;
	StringA m_straReloadRow;

	int GetFirstSelectedItem() const;
	OBJID GetFirstSelectedItemObjID() const;

	OBJID GetItemObjID(int nItem) const;
	int GetItemIndex(OBJID oid) const;

	virtual void Reload();
	void Reload(OBJID oid);

	BOOL CanDataDelete(StringA& fmtQuery);
	BOOL DataDelete(int* pnDelete, int nCount, PCCharA pcFormat);

	virtual BOOL ContextMenu(HMENU hMenu, UINT* puFlags, int iItem);
	virtual void DblClkItem(int nItem);

	virtual BOOL DataNew(OBJID& oid);
	virtual BOOL DataEdit(OBJID& oid);

	virtual BOOL GetSum(double& dSum) const;

	void SetStatusNumPaneText() const;
	void SetStatusSumPaneText() const;

	DECLARE_MESSAGE_MAP()
};


inline OBJID TableView::GetItemObjID(int nItem) const
{ return (OBJID)((nItem==-1)?0:GetListCtrl().GetItemData(nItem)); }

inline OBJID TableView::GetFirstSelectedItemObjID() const
{ return GetItemObjID(GetFirstSelectedItem()); }
