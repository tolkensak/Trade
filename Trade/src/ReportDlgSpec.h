
#pragma once

#include "ReportDlg.h"


class ReportDlgSpec : public ReportDlg
{
public:
	ReportDlgSpec(OBJID oidReport, CWnd* pParent=NULL);
	virtual ~ReportDlgSpec();

	virtual BOOL OnInitDialog();

protected:
	ReportFormPtr m_pForm;

	virtual ReportFormPtr GetActiveForm();

	DECLARE_MESSAGE_MAP()
};
