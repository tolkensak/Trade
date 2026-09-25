
#include "stdafx.h"
#include "App.h"
#include "BuyDlg.h"


BEGIN_MESSAGE_MAP(BuyDlg, DealDlg)
END_MESSAGE_MAP()


BuyDlg::BuyDlg(OBJID oidBuy, CWnd* pParent /*=NULL*/)
	: DealDlg(BuyDlg::IDD, oidBuy, "buy", pParent)
{
	m_rm.SetObject(ReloadMgr::objBuy);
}

BuyDlg::~BuyDlg()
{
}
