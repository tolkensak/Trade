
#include "stdafx.h"
#include "App.h"
#include "ReturnDlg.h"
#include "FormatStr.h"


BEGIN_MESSAGE_MAP(ReturnDlg, GridDlg)
	ON_BN_CLICKED(IDC_BTN_LIST, &ReturnDlg::OnBnClickedBtnList)
	ON_MESSAGE(UM_WARE_CHOOSED, &ReturnDlg::OnWareChoosed)
END_MESSAGE_MAP()


ReturnDlg::ReturnDlg(PCCharA pcaTable, CWnd* pParent /*=NULL*/)
	: GridDlg(ReturnDlg::IDD, pParent)
	, m_oidWare(0)
{
	m_straFormatReload.Format("call sp_%s_return_list(%%u, '%%S', '%%S')", pcaTable);
	m_straFormatApply.Format("delete from %s where %%s", pcaTable);

	int i=0;
	m_arrColumn.Add(Column(IDS_COL_WARE, Column::typeText, 100, i++));
	m_arrColumn.Add(Column(IDS_COL_AMOUNT, Column::typeFloat, 70, i++));
	m_arrColumn.Add(Column(IDS_COL_UNIT, Column::typeSymbol, 70, i++));
	m_arrColumn.Add(Column(IDS_COL_TOTAL, Column::typeMoney, 70, i++));
	m_arrColumn.Add(Column(IDS_COL_DEBT, Column::typeText, 100, i++));
	m_arrColumn.Add(Column(IDS_COL_MOMENT, Column::typeDateTime, 150, i++));
	m_arrColumn.Add(Column(IDS_COL_OPERATOR, Column::typeText, 100, i++));
}

ReturnDlg::~ReturnDlg()
{
}

BOOL ReturnDlg::OnInitDialog()
{
	GridDlg::OnInitDialog();

	m_edtWare.SubclassDlgItem(IDC_EDT_WARE, this);

	FormatStr fmtD(FormatStr::typeCtrl, FormatStr::partDate);
	FormatStr fmtT(FormatStr::typeCtrl, FormatStr::partTime);

	((CDateTimeCtrl*)GetDlgItem(IDC_DATE_FROM))->SetFormat(fmtD);
	((CDateTimeCtrl*)GetDlgItem(IDC_DATE_TO))->SetFormat(fmtD);

	((CDateTimeCtrl*)GetDlgItem(IDC_TIME_FROM))->SetFormat(fmtT);
	((CDateTimeCtrl*)GetDlgItem(IDC_TIME_TO))->SetFormat(fmtT);

	((CDateTimeCtrl*)GetDlgItem(IDC_TIME_FROM))->SetTime(COleDateTime(1900, 1, 1, 0, 0, 0));

	return TRUE;
}

LRESULT ReturnDlg::OnWareChoosed(WPARAM wp, LPARAM lp)
{
	m_oidWare=(OBJID)wp;

	StringA stra;
	stra.Format("call sp_return_ware(%u)", m_oidWare);

	MySQLResPtr pRes=theApp.Query(stra, this);
	if(!pRes)
		return 0;

	MYSQL_ROW row=pRes->FetchRow();
	if(!row)
		return 0;

	TCHAR pch[TOL_MAXSTR];
	PULONG len=pRes->FetchLengths();

	Utf8ToWchar(row[0], len[0], pch);
	SetDlgItemText(IDC_EDT_WARE, pch);

	return 0;
}

void ReturnDlg::OnBnClickedBtnList()
{
	if(m_oidWare==0)
		m_straReload.Empty();
	else
	{
		COleDateTime tm;
		COleDateTime from;
		COleDateTime to;

		FormatStr fmtDT(FormatStr::typeStore, FormatStr::partDateTime);

		((CDateTimeCtrl*)GetDlgItem(IDC_DATE_FROM))->GetTime(from);
		((CDateTimeCtrl*)GetDlgItem(IDC_TIME_FROM))->GetTime(tm);
		from.SetDateTime(from.GetYear(), from.GetMonth(), from.GetDay(), tm.GetHour(), tm.GetMinute(), tm.GetSecond());

		((CDateTimeCtrl*)GetDlgItem(IDC_DATE_TO))->GetTime(to);
		((CDateTimeCtrl*)GetDlgItem(IDC_TIME_TO))->GetTime(tm);
		to.SetDateTime(to.GetYear(), to.GetMonth(), to.GetDay(), tm.GetHour(), tm.GetMinute(), tm.GetSecond());

		m_straReload.Format(m_straFormatReload
			, m_oidWare
			, from.Format(fmtDT)
			, to.Format(fmtDT));
	}

	Reload();
}
