
#pragma once


class WareEdit : public CEdit
{
public:
	WareEdit();
	virtual ~WareEdit();

	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

protected:
	DECLARE_MESSAGE_MAP()
};
