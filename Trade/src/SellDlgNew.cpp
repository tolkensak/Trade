
#include "stdafx.h"
#include "App.h"
#include "SellDlgNew.h"


BEGIN_MESSAGE_MAP(SellDlgNew, SellDlg)
END_MESSAGE_MAP()


SellDlgNew::SellDlgNew(OBJID oidLot, CWnd* pParent /*=NULL*/)
	: SellDlg(0, pParent)
	, m_oidLot(oidLot)
{
	m_uTitleFormatID=IDS_TITLE_NEW;
}

SellDlgNew::~SellDlgNew()
{
}

void SellDlgNew::OnOK()
{
	if(!PrepareData())
		return;

	StringA stra;
	stra.Format("insert into sell_lot(lid, wid, amount, unid, price, total, debt, uid) \
					values(%u, %u, %f, %u, %f, %f, %s, %u)"
					, m_oidLot
					, m_oidWare
					, m_dAmount
					, m_oidUnit
					, m_dPrice
					, m_dTotal
					, (PCCharA)m_straDebt
					, theApp.GetUser().GetID());

	m_oid=theApp.Insert(stra, this);
	if(m_oid==0)
		return;

	m_rm.SetModified(ReloadMgr::oprNew);

	SellDlg::OnOK();
}
