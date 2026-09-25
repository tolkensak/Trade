
#pragma once

#include "ManipDlg.h"


class PermitDlg : public ManipDlg
{
protected:
	PermitDlg(UINT uIDTemplate, OBJID oidUser, CWnd* pParent=NULL);

public:
	virtual ~PermitDlg();

	DWORD GetPermit() const;

	void SetUser(const PermitDlg& dlg);
	void SetUser(OBJID oidUser, DWORD dwPermit);

	virtual BOOL OnInitDialog();

protected:
	BOOL m_bCheckStateChangable;
	BOOL m_bSetted;
	DWORD m_dwPermit;

	void Reload();

	virtual void UpdateCheckState()=0;
	virtual OBJID GetDesiredPermitID();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
};

inline OBJID PermitDlg::GetDesiredPermitID()
{ return ID_PERMIT_PERMIT; }

inline DWORD PermitDlg::GetPermit() const
{ return m_dwPermit; }
