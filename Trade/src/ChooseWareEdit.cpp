
#include "stdafx.h"
#include "App.h"
#include "ChooseWareEdit.h"
#include "ChooseWareDlg.h"


BEGIN_MESSAGE_MAP(ChooseWareEdit, CEdit)
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


ChooseWareEdit::ChooseWareEdit()
{
}

ChooseWareEdit::~ChooseWareEdit()
{
}

void ChooseWareEdit::Choose(UINT nChar)
{
	CString cstr;

	if(nChar)
		cstr=(TCHAR)nChar;
	else
		GetWindowText(cstr);

	ChooseWareDlg dlg(cstr);
	if(dlg.DoModal()==IDOK)
		GetParent()->SendMessage(UM_WARE_CHOOSED, (LPARAM)dlg.GetWareID(), 0);
}

void ChooseWareEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if(nChar==VK_DOWN)
		Choose();
	else if(nChar!=VK_UP)
		CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

void ChooseWareEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CEdit::OnChar(nChar, nRepCnt, nFlags);
	Choose(nChar);
}

void ChooseWareEdit::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CEdit::OnLButtonDblClk(nFlags, point);
	Choose();
}
