
#include "stdafx.h"
#include "App.h"
#include "BuyView.h"
#include "BuyDlgNew.h"
#include "BuyDlgEdit.h"
#include "BuyDebtDlg.h"
#include "BuyReturnDlg.h"


IMPLEMENT_DYNCREATE(BuyView, DealView)

BEGIN_MESSAGE_MAP(BuyView, DealView)
	ON_COMMAND(ID_DATA_BUY_DEBT, &BuyView::OnDataBuyDebt)
	ON_COMMAND(ID_DATA_BUY_RETURN, &BuyView::OnDataBuyReturn)
END_MESSAGE_MAP()


BuyView::BuyView()
	: DealView(IDR_BUY, "buy")
{
	m_rm.SetObject(ReloadMgr::objBuy);

	int i=0;
	m_arrColumn.Add(Column(IDS_COL_WARE, Column::typeText, 140, i++));
	m_arrColumn.Add(Column(IDS_COL_CAT, Column::typeText, 100, i++));
	m_arrColumn.Add(Column(IDS_COL_AMOUNT, Column::typeFloat, 70, i++));
	m_arrColumn.Add(Column(IDS_COL_UNIT, Column::typeSymbol, 70, i++));
	m_arrColumn.Add(Column(IDS_COL_PRICE, Column::typeMoney, 100, i++));
	m_arrColumn.Add(Column(IDS_COL_TOTAL, Column::typeMoney, 100, i++));
	m_arrColumn.Add(Column(IDS_COL_DEBT, Column::typeText, 100, i++));
	m_arrColumn.Add(Column(IDS_COL_MOMENT, Column::typeDateTime, 100, i++));
}

BuyView::~BuyView()
{
}

BOOL BuyView::DataNew(OBJID& oid)
{
	BuyDlgNew dlg(m_oidLot);
	if(dlg.DoModal()==IDOK)
	{
		oid=dlg.GetObjID();

		if(m_oidLot==0)
			ReloadLot(oid);

		return TRUE;
	}

	return FALSE;
}

BOOL BuyView::DataEdit(OBJID& oid)
{
	BuyDlgEdit dlg(oid);
	if(dlg.DoModal()==IDOK)
	{
		oid=dlg.GetObjID();
		return TRUE;
	}

	return FALSE;
}

void BuyView::OnDataBuyDebt()
{
	BuyDebtDlg dlg;
	dlg.DoModal();
}

void BuyView::OnDataBuyReturn()
{
	BuyReturnDlg dlg;
	dlg.DoModal();
}
