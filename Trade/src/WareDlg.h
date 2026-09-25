
#pragma once

#include "ManipDlg.h"


class WareDlg : public ManipDlg
{
protected:
	WareDlg(OBJID oidWare, CWnd* pParent=NULL);

public:
	virtual ~WareDlg();

	enum { IDD=IDD_WARE };

	virtual BOOL OnInitDialog();

	afx_msg void OnCbnSelChangeCmbWareCat();
	afx_msg void OnBnClickedBtnWareCat();

	afx_msg void OnCbnSelChangeCmbFirm();
	afx_msg void OnBnClickedBtnFirm();

	afx_msg void OnCbnSelChangeCmbUnitCat();
	afx_msg void OnBnClickedBtnUnitCat();

protected:
	OBJID m_oidWareCat;
	OBJID m_oidUnitCat;
	OBJID m_oidFirm;

	void ReloadCmbWareCat();
	void ReloadCmbUnitCat();

	virtual BOOL IsValid(ValidStr& cstrName);
	virtual void ReloadCmbFirm();
	virtual OBJID GetDesiredPermitID();

	DECLARE_MESSAGE_MAP()
};

inline OBJID WareDlg::GetDesiredPermitID()
{ return ID_PERMIT_EDIT_WARE; }
