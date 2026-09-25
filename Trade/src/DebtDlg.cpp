
#include "stdafx.h"
#include "App.h"
#include "DebtDlg.h"


BEGIN_MESSAGE_MAP(DebtDlg, GridDlg)
END_MESSAGE_MAP()


DebtDlg::DebtDlg(PCCharA pcaTable, CWnd* pParent /*=NULL*/)
	: GridDlg(DebtDlg::IDD, pParent)
{
	m_straReload.Format("call sp_%s_debt_list()", pcaTable);
	m_straFormatApply.Format("update %s set debt=null where %%s", pcaTable);

	int i=0;
	m_arrColumn.Add(Column(IDS_COL_DEBT, Column::typeText, 100, i++));
	m_arrColumn.Add(Column(IDS_COL_WARE, Column::typeText, 100, i++));
	m_arrColumn.Add(Column(IDS_COL_CAT, Column::typeText, 100, i++));
	m_arrColumn.Add(Column(IDS_COL_FIRM, Column::typeText, 100, i++));
	m_arrColumn.Add(Column(IDS_COL_AMOUNT, Column::typeFloat, 70, i++));
	m_arrColumn.Add(Column(IDS_COL_UNIT, Column::typeSymbol, 70, i++));
	m_arrColumn.Add(Column(IDS_COL_TOTAL, Column::typeMoney, 70, i++));
	m_arrColumn.Add(Column(IDS_COL_MOMENT, Column::typeDateTime, 150, i++));
	m_arrColumn.Add(Column(IDS_COL_OPERATOR, Column::typeText, 100, i++));
}

DebtDlg::~DebtDlg()
{
}
