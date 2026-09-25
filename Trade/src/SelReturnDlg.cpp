
#include "stdafx.h"
#include "App.h"
#include "SellReturnDlg.h"


BEGIN_MESSAGE_MAP(SellReturnDlg, ReturnDlg)
END_MESSAGE_MAP()


SellReturnDlg::SellReturnDlg(CWnd* pParent /*=NULL*/)
	: ReturnDlg("sell", pParent)
{
	m_uTitleID=IDS_TITLE_SELL_RETURN;
}

SellReturnDlg::~SellReturnDlg()
{
}
