
#pragma once

#include "TableDlg.h"
#include "ReportForm.h"


class ReportDlg : public TableDlg
{
protected:
	ReportDlg(OBJID oidReport, CWnd* pParent=NULL);

public:
	virtual ~ReportDlg();

	enum { IDD=IDD_REPORT };

	void GetDlgUnit(double& dx, double& dy);

	virtual BOOL OnInitDialog();

protected:
	UINT m_uCtrlID;
	OBJID m_oidReport;

	BOOL CreateReport();
	ReportFormPtr CreateForm(OBJID oidForm);

	virtual HWND GetInsertAfter();
	virtual ReportFormPtr GetActiveForm()=0;
	virtual void GetRectForForm(CRect& rc);
	virtual OBJID GetDesiredPermitID();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
};

inline OBJID ReportDlg::GetDesiredPermitID()
{ return ID_PERMIT_REPORT; }
