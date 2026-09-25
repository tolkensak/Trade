
#pragma once

#include "ManipDlg.h"
#include "ChooseWareEdit.h"


class DealDlg : public ManipDlg
{
protected:
	DealDlg(UINT uIDTemplate, OBJID oidDeal, PCCharA pcTablePrefix, CWnd* pParent=NULL);

public:
	virtual ~DealDlg();

	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedBtnWare();
	afx_msg void OnBnClickedBtnPrice();
	afx_msg void OnCbnSelChangeCmbUnit();
	afx_msg void OnEnChangeEdtPrice();
	afx_msg void OnEnChangeEdtAmount();
	afx_msg void OnEnChangeEdtTotal();
	afx_msg void OnBnClickedChkCalcAmount();
	afx_msg LRESULT OnWareChoosed(WPARAM wp, LPARAM lp);

protected:
	ChooseWareEdit m_edtWare;
	StringA m_straTablePrefix;
	CString m_strOrgPrice;
	StringA m_straDebt;

	BOOL m_bCalcAmount;

	OBJID m_oidWare;
	OBJID m_oidUnit;
	OBJID m_oidUnitCat;

	double m_dRatio;
	double m_dAmount;
	double m_dPrice;
	double m_dTotal;


	void UpdateCalcState();
	void ChangeCalcState();

	void Reload();
	void ReloadCmbUnit();

	void Calc();
	BOOL PrepareData();

	DECLARE_MESSAGE_MAP()
};
