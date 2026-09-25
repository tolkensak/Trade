
#include "stdafx.h"
#include "App.h"
#include "PriceDlg.h"


PriceDlg::Data::Data(OBJID oid)
	: oid(oid)
	, dSpend(0)
	, dAppend(0)
	, bPercent(FALSE)
{
}

PriceDlg::Data::~Data()
{
}

BOOL operator==(const PriceDlg::Data& data1, const PriceDlg::Data& data2)
{
	return (data1.oid==data2.oid
		&& data1.dSpend==data2.dSpend
		&& data1.dAppend==data2.dAppend
		&& data1.bPercent==data2.bPercent);
}


BEGIN_MESSAGE_MAP(PriceDlg, ManipDlg)
END_MESSAGE_MAP()


PriceDlg::PriceDlg(OBJID oidWare, CWnd* pParent /*=NULL*/)
	: ManipDlg(PriceDlg::IDD, oidWare, pParent)
	, m_oidUnitCat(0)
{
	m_rm.SetObject(ReloadMgr::objPrice);
	m_uTitleFormatID=IDS_TITLE_CHANGE;
}

PriceDlg::~PriceDlg()
{
}

void PriceDlg::ReloadCmbUnit()
{
	StringA stra;
	stra.Format("select id, name from unit where ucid=%u order by main desc, ratio", m_oidUnitCat);
	CbReload(IDC_CMB_UNIT, stra, 0);
}

void PriceDlg::Reload()
{
	m_pDataOrg=new Data(m_oid);

	if(m_oid==0)
	{
		SetDlgItemText(IDC_EDT_WARE, _T(""));
		CbReload(IDC_CMB_UNIT, _T(""));
		SetDlgItemText(IDC_EDT_SPEND, _T(""));
		SetDlgItemText(IDC_EDT_APPEND, _T(""));
		CheckDlgButton(IDC_CHK_PERCENT, 0);
		return;
	}

	StringA stra;
	stra.Format("call sp_price_reload(%u)", m_oid);

	MySQLResPtr pRes=theApp.Query(stra, this);
	if(!pRes)
		return;

	MYSQL_ROW row=pRes->FetchRow();
	if(!row)
		return;

	PULONG len=pRes->FetchLengths();
	TCHAR pch[TOL_MAXSTR];

	int i=0; // ware name
	Utf8ToWchar(row[i], len[i], pch);
	SetDlgItemText(IDC_EDT_WARE, pch);

	i++; // unit
	m_oidUnitCat=atoi(row[i]);

	i++; // spend
	Utf8ToWchar(row[i], len[i], pch);
	SetDlgItemText(IDC_EDT_SPEND, pch);
	m_pDataOrg->dSpend=_tstof(pch);

	i++; // append
	Utf8ToWchar(row[i], len[i], pch);
	SetDlgItemText(IDC_EDT_APPEND, pch);
	m_pDataOrg->dAppend=_tstof(pch);

	i++; // percent
	m_pDataOrg->bPercent=atoi(row[i]);
	CheckDlgButton(IDC_CHK_PERCENT, m_pDataOrg->bPercent);

	ReloadCmbUnit();
}

BOOL PriceDlg::PrepareData(Data& data)
{
	if(data.oid==0)
	{
		ShowInfo(IDC_EDT_WARE, IDS_BAD_TEXT);
		return FALSE;
	}

	OBJID oidUnit=CbGetOid(IDC_CMB_UNIT);
	if(oidUnit==0)
	{
		ShowInfo(IDC_CMB_UNIT, IDS_BAD_SELECT);
		return FALSE;
	}

	double dRatio=GetUnitRatio(oidUnit);
	if(dRatio==0)
	{
		ShowInfo(IDC_CMB_UNIT, IDS_BAD_SELECT);
		return FALSE;
	}

	ValidStr cstrSpend;
	GetDlgItemText(IDC_EDT_SPEND, cstrSpend);
	if(!cstrSpend.IsValidNumber())
	{
		ShowInfo(IDC_EDT_SPEND, IDS_BAD_TEXT);
		return FALSE;
	}

	ValidStr cstrAppend;
	GetDlgItemText(IDC_EDT_APPEND, cstrAppend);
	if(!cstrAppend.IsValidNumber())
	{
		ShowInfo(IDC_EDT_APPEND, IDS_BAD_TEXT);
		return FALSE;
	}

	data.bPercent=IsDlgButtonChecked(IDC_CHK_PERCENT);

	data.dSpend=_tstof(cstrSpend)/dRatio;
	if(data.dSpend==0)
	{
		ShowInfo(IDC_EDT_SPEND, IDS_BAD_TEXT);
		return FALSE;
	}

	data.dAppend=_tstof(cstrAppend)/(data.bPercent?1:dRatio);
	if(data.dAppend==0)
	{
		ShowInfo(IDC_EDT_APPEND, IDS_BAD_TEXT);
		return FALSE;
	}

	return TRUE;
}

void PriceDlg::OnOK()
{
	Data data(m_oid);

	if(!PrepareData(data))
		return;

	if(!m_pDataOrg)
		return;

	if(*m_pDataOrg==data)
	{
		PriceDlg::OnCancel();
		return;
	}

	StringA stra;
	stra.Format("insert into price(wid, spend, append, percent, uid) \
				values(%u, %f, %f, %u, %u)"
					, data.oid
					, data.dSpend
					, data.dAppend
					, data.bPercent
					, theApp.GetUser().GetID());

	if(!theApp.Exec(stra, this))
		return;

	m_rm.SetModified(ReloadMgr::oprEdit);

	ManipDlg::OnOK();
}
