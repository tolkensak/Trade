
#pragma once

#include "Dialog.h"


class TableDlg : public Dialog
{
protected:
	TableDlg(UINT uIDTemplate, CWnd* pParent=NULL);

public:
	virtual ~TableDlg();

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

protected:
	OBJID CbGetOid(UINT uCtrlID, int nItem=-1);
	void CbSelect(UINT uCtrlID, int nSelect=-1, OBJID oidSelect=0);
	void CbReload(UINT uCtrlID, const StringA& straQuery, int nSelect=-1, OBJID oidSelect=0, BOOL bIncludeAll=FALSE);

	virtual OBJID GetDesiredPermitID()=0;

	DECLARE_MESSAGE_MAP()
};

inline OBJID TableDlg::CbGetOid(UINT uCtrlID, int nItem)
{ return Cb_GetOid((CComboBox*)GetDlgItem(uCtrlID), nItem); }

inline void TableDlg::CbSelect(UINT uCtrlID, int nSelect, OBJID oidSelect)
{ return Cb_Select((CComboBox*)GetDlgItem(uCtrlID), nSelect, oidSelect); }

inline void TableDlg::CbReload(UINT uCtrlID, const StringA& straQuery, int nSelect, OBJID oidSelect, BOOL bIncludeAll)
{ return Cb_Reload((CComboBox*)GetDlgItem(uCtrlID), straQuery, nSelect, oidSelect, bIncludeAll); }
