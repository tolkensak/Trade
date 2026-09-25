
#pragma once

#include "Dialog.h"
#include "WareEdit.h"
#include "WareList.h"


class ChooseWareDlg : public Dialog
{
public:
	ChooseWareDlg(LPCTSTR pcInit, CWnd* pParent=NULL);
	virtual ~ChooseWareDlg();

	enum { IDD=IDD_CHOOSE_WARE };

	OBJID GetWareID() const;

	virtual BOOL OnInitDialog();

	afx_msg void OnEnChangeEdtWare();
	afx_msg void OnLvnItemChangedList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblClkList(NMHDR *pNMHDR, LRESULT *pResult);

protected:
	WareEdit m_edit;
	WareList m_list;

	OBJID m_oid;
	CString m_strInit;

	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
};

inline OBJID ChooseWareDlg::GetWareID() const
{ return m_oid; }
