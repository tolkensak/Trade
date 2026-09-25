
#pragma once


class Dialog : public CDialog
{
protected:
	Dialog(UINT uIDTemplate, CWnd* pParent=NULL);

public:
	virtual ~Dialog();

	virtual BOOL OnInitDialog();

protected:
	UINT m_uTitleID;
	UINT m_uTitleFormatID;

	static HICON s_hIconNew;
	static HICON s_hIconPrice;

	void SetButtonIcon(UINT uBtnID, HICON hIcon);
	int ShowInfo(UINT uCtrlID, UINT uTextID, UINT uType=MB_OK|MB_ICONINFORMATION);

	DECLARE_MESSAGE_MAP()
};
