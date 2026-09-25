
#include "stdafx.h"
#include "App.h"
#include "SellDlg.h"



BEGIN_MESSAGE_MAP(SellDlg, DealDlg)
	ON_BN_CLICKED(IDC_CHK_FREE_PRICE, &SellDlg::OnBnClickedChkFreePrice)
END_MESSAGE_MAP()


SellDlg::SellDlg(OBJID oidSell, CWnd* pParent /*=NULL*/)
	: DealDlg(SellDlg::IDD, oidSell, "sell", pParent)
	, m_bFreePrice(FALSE)
{
	m_rm.SetObject(ReloadMgr::objSell);
}

SellDlg::~SellDlg()
{
}

void SellDlg::UpdatePriceState()
{
	CheckDlgButton(IDC_CHK_FREE_PRICE, m_bFreePrice);
	ChangePriceState();
}

void SellDlg::ChangePriceState()
{
	SendDlgItemMessage(IDC_EDT_PRICE, EM_SETREADONLY, !m_bFreePrice);
	if(!m_bFreePrice)
		SetDlgItemText(IDC_EDT_PRICE, m_strOrgPrice);
}

BOOL SellDlg::OnInitDialog()
{
	DealDlg::OnInitDialog();
	UpdatePriceState();
	return TRUE;
}

void SellDlg::OnBnClickedChkFreePrice()
{
	m_bFreePrice=IsDlgButtonChecked(IDC_CHK_FREE_PRICE);
	ChangePriceState();
}
