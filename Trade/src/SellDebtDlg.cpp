
#include "stdafx.h"
#include "App.h"
#include "SellDebtDlg.h"


BEGIN_MESSAGE_MAP(SellDebtDlg, DebtDlg)
END_MESSAGE_MAP()


SellDebtDlg::SellDebtDlg(CWnd* pParent /*=NULL*/)
	: DebtDlg("sell", pParent)
{
	m_uTitleID=IDS_TITLE_SELL_DEBT;
}

SellDebtDlg::~SellDebtDlg()
{
}
