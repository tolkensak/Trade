
#include "stdafx.h"
#include "App.h"
#include "DealDlg.h"
#include "WareDlgNew.h"
#include "PriceDlgSpec.h"


BEGIN_MESSAGE_MAP(DealDlg, ManipDlg)
	ON_BN_CLICKED(IDC_BTN_WARE, &DealDlg::OnBnClickedBtnWare)
	ON_BN_CLICKED(IDC_BTN_PRICE, &DealDlg::OnBnClickedBtnPrice)
	ON_CBN_SELCHANGE(IDC_CMB_UNIT, &DealDlg::OnCbnSelChangeCmbUnit)
	ON_EN_CHANGE(IDC_EDT_PRICE, &DealDlg::OnEnChangeEdtPrice)
	ON_EN_CHANGE(IDC_EDT_AMOUNT, &DealDlg::OnEnChangeEdtAmount)
	ON_EN_CHANGE(IDC_EDT_TOTAL, &DealDlg::OnEnChangeEdtTotal)
	ON_BN_CLICKED(IDC_CHK_CALC_AMOUNT, &DealDlg::OnBnClickedChkCalcAmount)
	ON_MESSAGE(UM_WARE_CHOOSED, &DealDlg::OnWareChoosed)
END_MESSAGE_MAP()


DealDlg::DealDlg(UINT uIDTemplate, OBJID oidDeal, PCCharA pcTablePrefix, CWnd* pParent /*=NULL*/)
	: ManipDlg(uIDTemplate, oidDeal, pParent)
	, m_straTablePrefix(pcTablePrefix)
	, m_bCalcAmount(FALSE)
	, m_oidWare(0)
	, m_oidUnit(0)
	, m_oidUnitCat(0)
	, m_dRatio(0)
	, m_dAmount(0)
	, m_dPrice(0)
	, m_dTotal(0)
{
}

DealDlg::~DealDlg()
{
}

void DealDlg::ReloadCmbUnit()
{
	StringA stra;
	stra.Format("select id, name from unit where ucid=%u order by main desc, ratio", m_oidUnitCat);
	CbReload(IDC_CMB_UNIT, stra, m_oidUnit?-1:0, m_oidUnit);
}

void DealDlg::Reload()
{
	if(m_oidWare==0)
	{
		SetDlgItemText(IDC_EDT_WARE, _T(""));
		CbReload(IDC_CMB_UNIT, _T(""));
		SetDlgItemText(IDC_EDT_PRICE, _T(""));
		return;
	}

	StringA stra;
	stra.Format("call sp_%s_lot_reload(%u)", (PCCharA)m_straTablePrefix, m_oidWare);

	MySQLResPtr pRes=theApp.Query(stra, this);
	if(!pRes)
		return;

	MYSQL_ROW row=pRes->FetchRow();
	if(!row)
		return;

	TCHAR pch[TOL_MAXSTR];
	PULONG len=pRes->FetchLengths();

	int i=0;
	Utf8ToWchar(row[i], len[i], pch);
	SetDlgItemText(IDC_EDT_WARE, pch);

	i++;
	Utf8ToWchar(row[i], len[i], pch);
	SetDlgItemText(IDC_EDT_PRICE, pch);
	m_strOrgPrice=pch;

	i++; // unit_cat
	m_oidUnitCat=atoi(row[i]);

	ReloadCmbUnit();
	OnCbnSelChangeCmbUnit();

	GetDlgItem(m_bCalcAmount?IDC_EDT_TOTAL:IDC_EDT_AMOUNT)->SetFocus();
}

void DealDlg::UpdateCalcState()
{
	CheckDlgButton(IDC_CHK_CALC_AMOUNT, m_bCalcAmount);
	ChangeCalcState();
}

void DealDlg::ChangeCalcState()
{
	SendDlgItemMessage(IDC_EDT_AMOUNT, EM_SETREADONLY, m_bCalcAmount);
	SendDlgItemMessage(IDC_EDT_TOTAL, EM_SETREADONLY, !m_bCalcAmount);
}

BOOL DealDlg::OnInitDialog()
{
	ManipDlg::OnInitDialog();
	m_edtWare.SubclassDlgItem(IDC_EDT_WARE, this);

	UpdateCalcState();
	return TRUE;
}

LRESULT DealDlg::OnWareChoosed(WPARAM wp, LPARAM lp)
{
	m_oidWare=(OBJID)wp;
	m_oidUnit=0;
	Reload();

	return 0;
}

void DealDlg::OnBnClickedBtnWare()
{
	WareDlgNew dlg;
	if(dlg.DoModal()==IDOK)
	{
		m_oidWare=dlg.GetObjID();
		m_oidUnit=0;
		Reload();
	}
}

void DealDlg::OnBnClickedBtnPrice()
{
	if(!m_oidWare)
		return;

	PriceDlgSpec dlg(m_oidWare);
	if(dlg.DoModal()!=IDOK)
		return;

	StringA stra;
	stra.Format("call sp_%s_price(%u)", (PCCharA)m_straTablePrefix, m_oidWare);

	MySQLResPtr pRes=theApp.Query(stra, this);
	if(!pRes)
		return;

	MYSQL_ROW row=pRes->FetchRow();
	if(!row)
		return;

	TCHAR pch[TOL_MAXSTR];
	PULONG len=pRes->FetchLengths();

	Utf8ToWchar(row[0], len[0], pch);
	SetDlgItemText(IDC_EDT_PRICE, pch);
}

void DealDlg::OnBnClickedChkCalcAmount()
{
	m_bCalcAmount=IsDlgButtonChecked(IDC_CHK_CALC_AMOUNT);
	ChangeCalcState();
	GetDlgItem(m_bCalcAmount?IDC_EDT_TOTAL:IDC_EDT_AMOUNT)->SetFocus();
}

void DealDlg::OnCbnSelChangeCmbUnit()
{
	m_oidUnit=CbGetOid(IDC_CMB_UNIT);

	if(m_oidUnit==0)
	{
		m_dRatio=0;
		Calc();
	}
	else
	{
		double d=GetUnitRatio(m_oidUnit);
		if(d!=m_dRatio)
		{
			m_dRatio=d;
			Calc();
		}
	}
}

void DealDlg::OnEnChangeEdtPrice()
{
	ValidStr cstr;
	GetDlgItemText(IDC_EDT_PRICE, cstr);
	if(!cstr.IsValidNumber())
	{
		m_dPrice=0;
		Calc();
		return;
	}

	double d=_tstof(cstr);
	if(d!=m_dPrice)
	{
		m_dPrice=d;
		Calc();
	}
}

void DealDlg::OnEnChangeEdtAmount()
{
	if(m_bCalcAmount)
		return;

	ValidStr cstr;
	GetDlgItemText(IDC_EDT_AMOUNT, cstr);
	if(!cstr.IsValidNumber())
	{
		m_dAmount=0;
		Calc();
		return;
	}

	double d=_tstof(cstr);
	if(d!=m_dAmount)
	{
		m_dAmount=d;
		Calc();
	}
}

void DealDlg::OnEnChangeEdtTotal()
{
	if(!m_bCalcAmount)
		return;

	ValidStr cstr;
	GetDlgItemText(IDC_EDT_TOTAL, cstr);
	if(!cstr.IsValidNumber())
	{
		m_dTotal=0;
		Calc();
		return;
	}

	double d=_tstof(cstr);
	if(d!=m_dTotal)
	{
		m_dTotal=d;
		Calc();
	}
}

void DealDlg::Calc()
{
	CString cstr;

	if(m_bCalcAmount)
	{
		if(m_dRatio && m_dPrice)
			m_dAmount=m_dTotal/m_dRatio/m_dPrice;
		else
			m_dAmount=0;

		cstr.Format(_T("%f"), m_dAmount);
		SetDlgItemText(IDC_EDT_AMOUNT, cstr);
	}
	else
	{
		m_dTotal=m_dAmount*m_dRatio*m_dPrice;

		cstr.Format(_T("%.2f"), m_dTotal);
		SetDlgItemText(IDC_EDT_TOTAL, cstr);
	}
}

BOOL DealDlg::PrepareData()
{
	if(m_oidWare==0)
	{
		ShowInfo(IDC_EDT_WARE, IDS_BAD_TEXT);
		return FALSE;
	}

	if(m_dAmount==0)
	{
		ShowInfo(IDC_EDT_AMOUNT, IDS_BAD_TEXT);
		return FALSE;
	}

	if(m_oidUnit==0)
	{
		ShowInfo(IDC_CMB_UNIT, IDS_BAD_SELECT);
		return FALSE;
	}

	if(m_dRatio==0)
	{
		ShowInfo(IDC_CMB_UNIT, IDS_BAD_SELECT);
		return FALSE;
	}

	if(m_dPrice==0)
	{
		ShowInfo(IDC_EDT_PRICE, IDS_BAD_TEXT);
		return FALSE;
	}

	if(m_dTotal==0)
	{
		ShowInfo(IDC_EDT_TOTAL, IDS_BAD_TEXT);
		return FALSE;
	}

	CString cstr;
	GetDlgItemText(IDC_EDT_DEBT, cstr);
	cstr.Trim();
	if(cstr.IsEmpty())
		m_straDebt="null";
	else
		m_straDebt.Format("'%s'", WcharToUtf8(cstr));

	return TRUE;
}
