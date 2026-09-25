
#pragma once

#include "ReportDlg.h"


class ReportDlgGlob : public ReportDlg
{
public:
	ReportDlgGlob(CWnd* pParent=NULL);
	virtual ~ReportDlgGlob();

	virtual BOOL OnInitDialog();

	afx_msg void OnNMDblClkList(NMHDR *pNMHDR, LRESULT *pResult);

protected:
	OBJID m_oidForm;
	ReportFormPtrMap m_mapForm;

	void ChangeReport(int nItem=-1);
	void ChangeForm(OBJID oidForm);

	virtual HWND GetInsertAfter();
	virtual ReportFormPtr GetActiveForm();
	virtual void GetRectForForm(CRect& rc);
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
};
