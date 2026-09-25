
#pragma once

#include "PriceDlg.h"
#include "ChooseWareEdit.h"


class PriceDlgGlob : public PriceDlg
{
public:
	PriceDlgGlob(CWnd* pParent=NULL);
	virtual ~PriceDlgGlob();

	afx_msg LRESULT OnWareChoosed(WPARAM wp, LPARAM lp);

	virtual BOOL OnInitDialog();

protected:
	ChooseWareEdit m_edtWare;

	DECLARE_MESSAGE_MAP()
};
