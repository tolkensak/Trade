
#include "stdafx.h"
#include "App.h"
#include "SellDlgEdit.h"


BEGIN_MESSAGE_MAP(SellDlgEdit, SellDlg)
END_MESSAGE_MAP()


SellDlgEdit::SellDlgEdit(OBJID oidSell, CWnd* pParent /*=NULL*/)
	: SellDlg(oidSell, pParent)
{
	m_uTitleFormatID=IDS_TITLE_EDIT;
}

SellDlgEdit::~SellDlgEdit()
{
}

BOOL SellDlgEdit::OnInitDialog()
{
	SellDlg::OnInitDialog();

	StringA stra;
	stra.Format("call sp_sell_lot_edit(%u)", m_oid);

	MySQLResPtr pRes=theApp.Query(stra, this);
	if(!pRes)
		return TRUE;

	MYSQL_ROW row=pRes->FetchRow();
	if(!row)
		return TRUE;

	PULONG len=pRes->FetchLengths();
	TCHAR pch[TOL_MAXSTR];

	int i=0; // ware name
	Utf8ToWchar(row[i], len[i], pch);
	SetDlgItemText(IDC_EDT_WARE, pch);

	i++; // ware id
	m_oidWare=atoi(row[i]);

	i++; // amount
	Utf8ToWchar(row[i], len[i], pch);
	SetDlgItemText(IDC_EDT_AMOUNT, pch);

	i++; // unit id
	m_oidUnit=atoi(row[i]);

	i++; // price
	Utf8ToWchar(row[i], len[i], pch);
	SetDlgItemText(IDC_EDT_PRICE, pch);
	CString strPrice=pch;

	i++; // total
	Utf8ToWchar(row[i], len[i], pch);
	SetDlgItemText(IDC_EDT_TOTAL, pch);

	i++; // debt
	if(row[i])
		Utf8ToWchar(row[i], len[i], pch);
	else
		pch[0]=_T('\0');

	SetDlgItemText(IDC_EDT_DEBT, pch);

	i++; // unit_cat
	m_oidUnitCat=atoi(row[i]);

	i++; // ware price
	Utf8ToWchar(row[i], len[i], pch);
	m_strOrgPrice=pch;

	m_bFreePrice=(strPrice!=m_strOrgPrice);
	UpdatePriceState();

	ReloadCmbUnit();
	OnCbnSelChangeCmbUnit();

	GetDlgItem(IDC_EDT_AMOUNT)->SetFocus();

	return FALSE;
}

void SellDlgEdit::OnOK()
{
	if(!PrepareData())
		return;

	StringA stra;
	stra.Format("update sell_lot set wid=%u, amount=%f, unid=%u, price=%f, total=%f, debt=%s where id=%u"
					, m_oidWare
					, m_dAmount
					, m_oidUnit
					, m_dPrice
					, m_dTotal
					, (PCCharA)m_straDebt
					, m_oid);

	if(!theApp.Exec(stra, this))
		return;

	m_rm.SetModified(ReloadMgr::oprEdit);

	SellDlg::OnOK();
}
