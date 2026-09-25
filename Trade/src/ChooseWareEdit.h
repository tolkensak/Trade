
#pragma once


class ChooseWareEdit : public CEdit
{
public:
	ChooseWareEdit();
	virtual ~ChooseWareEdit();

	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

protected:
	void Choose(UINT nChar=0);

	DECLARE_MESSAGE_MAP()
};
