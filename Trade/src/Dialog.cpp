
#include "stdafx.h"
#include "Dialog.h"
#include "resource.h"


HICON Dialog::s_hIconNew=NULL;
HICON Dialog::s_hIconPrice=NULL;


BEGIN_MESSAGE_MAP(Dialog, CDialog)
END_MESSAGE_MAP()


Dialog::Dialog(UINT uIDTemplate, CWnd* pParent /*=NULL*/)
	: CDialog(uIDTemplate, pParent)
	, m_uTitleFormatID(0)
	, m_uTitleID(0)
{
	if(!s_hIconNew)
		s_hIconNew=(HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_NEW_REG), IMAGE_ICON, 0, 0, LR_SHARED);

	if(!s_hIconPrice)
		s_hIconPrice=(HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_PRICE_REG), IMAGE_ICON, 0, 0, LR_SHARED);
}

Dialog::~Dialog()
{
}

void Dialog::SetButtonIcon(UINT uBtnID, HICON hIcon)
{
	if(!hIcon)
		return;

	CButton* pBtn=(CButton*)GetDlgItem(uBtnID);
	if(!pBtn)
		return;

	SetWindowLongPtr(pBtn->GetSafeHwnd(), GWL_STYLE, GetWindowLongPtr(pBtn->GetSafeHwnd(), GWL_STYLE)|BS_ICON|BS_FLAT);
	pBtn->SetIcon(hIcon);
}

BOOL Dialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(m_uTitleFormatID)
	{
		CString cstrFormat;
		cstrFormat.LoadString(m_uTitleFormatID);

		CString cstrObject;
		if(m_uTitleID)
			cstrObject.LoadString(m_uTitleID);
		else
			GetWindowText(cstrObject);

		CString cstrTitle;
		cstrTitle.Format(cstrFormat, cstrObject);
		SetWindowText(cstrTitle);
	}
	else if(m_uTitleID)
	{
		CString cstrTitle;
		cstrTitle.LoadString(m_uTitleID);
		SetWindowText(cstrTitle);
	}

	SetButtonIcon(IDC_BTN_WARE, s_hIconNew);
	SetButtonIcon(IDC_BTN_CAT, s_hIconNew);
	SetButtonIcon(IDC_BTN_WARE_CAT, s_hIconNew);
	SetButtonIcon(IDC_BTN_UNIT_CAT, s_hIconNew);
	SetButtonIcon(IDC_BTN_FIRM, s_hIconNew);
	SetButtonIcon(IDC_BTN_CLIENT, s_hIconNew);
	SetButtonIcon(IDC_BTN_PRICE, s_hIconPrice);
	SetButtonIcon(IDC_BTN_WARE, s_hIconNew);
	SetButtonIcon(IDC_BTN_WARE, s_hIconNew);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

int Dialog::ShowInfo(UINT uCtrlID, UINT uTextID, UINT uType)
{
	CWnd* pWnd=GetDlgItem(uCtrlID);
	if(!pWnd)
		return 0;

	CString cstr;
	pWnd->GetWindow(GW_HWNDPREV)->GetWindowText(cstr);
	cstr.Remove(_T('&'));

	int nRet=MsgBox(this, uType, uTextID, cstr);

	pWnd->SetFocus();

	return nRet;
}
