
#pragma once

#include "GridDlg.h"
#include "ChooseWareEdit.h"


class ReturnDlg : public GridDlg
{
protected:
	ReturnDlg(PCCharA pcaTable, CWnd* pParent=NULL);

public:
	virtual ~ReturnDlg();

	enum { IDD=IDD_RETURN };

	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedBtnList();
	afx_msg LRESULT OnWareChoosed(WPARAM wp, LPARAM lp);

protected:
	OBJID m_oidWare;
	ChooseWareEdit m_edtWare;
	StringA m_straFormatReload;

	DECLARE_MESSAGE_MAP()
};
