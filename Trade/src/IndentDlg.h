
#pragma once

#include "ManipDlg.h"


class IndentDlg : public ManipDlg
{
protected:
	IndentDlg(OBJID oidIndent, CWnd* pParent=NULL);

public:
	virtual ~IndentDlg();

	enum { IDD=IDD_INDENT };

	virtual BOOL OnInitDialog();

	afx_msg void OnCbnSelChangeCmbClient();
	afx_msg void OnBnClickedBtnClient();

protected:
	OBJID m_oidClient;
	CString m_strDeliver;

	BOOL PrepareData();

	virtual void ReloadCmbClient();
	virtual OBJID GetDesiredPermitID();

	DECLARE_MESSAGE_MAP()
};

inline OBJID IndentDlg::GetDesiredPermitID()
{ return ID_PERMIT_INDENT; }
