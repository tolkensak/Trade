
#include "stdafx.h"
#include "App.h"
#include "BuyDebtDlg.h"


BEGIN_MESSAGE_MAP(BuyDebtDlg, DebtDlg)
END_MESSAGE_MAP()


BuyDebtDlg::BuyDebtDlg(CWnd* pParent /*=NULL*/)
	: DebtDlg("buy", pParent)
{
	m_uTitleID=IDS_TITLE_BUY_DEBT;
}

BuyDebtDlg::~BuyDebtDlg()
{
}
