
#include "stdafx.h"
#include "App.h"
#include "BuyReturnDlg.h"


BEGIN_MESSAGE_MAP(BuyReturnDlg, ReturnDlg)
END_MESSAGE_MAP()


BuyReturnDlg::BuyReturnDlg(CWnd* pParent /*=NULL*/)
	: ReturnDlg("buy", pParent)
{
	m_uTitleID=IDS_TITLE_BUY_RETURN;
}

BuyReturnDlg::~BuyReturnDlg()
{
}
