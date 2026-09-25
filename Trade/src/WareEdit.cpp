
#include "stdafx.h"
#include "WareEdit.h"


BEGIN_MESSAGE_MAP(WareEdit, CEdit)
	ON_WM_SETFOCUS()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


WareEdit::WareEdit()
{
}

WareEdit::~WareEdit()
{
}

void WareEdit::OnSetFocus(CWnd* pOldWnd)
{
	CEdit::OnSetFocus(pOldWnd);
	SetSel(-1, 0);
}

void WareEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if(nChar==VK_DOWN)
		GetParent()->GetNextDlgTabItem(this)->SetFocus();
	else if(nChar!=VK_UP)
		CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}
