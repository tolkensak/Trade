
#include "stdafx.h"
#include "App.h"
#include "UnitDlgNew.h"
#include "UnitCatDlgNew.h"


BEGIN_MESSAGE_MAP(UnitDlgNew, UnitDlg)
	ON_CBN_SELCHANGE(IDC_CMB_CAT, &UnitDlgNew::OnCbnSelChangeCmbCat)
	ON_BN_CLICKED(IDC_BTN_CAT, &UnitDlgNew::OnBnClickedBtnCat)
END_MESSAGE_MAP()


UnitDlgNew::UnitDlgNew(CWnd* pParent /*=NULL*/)
	: UnitDlg(0, pParent)
{
	m_uTitleFormatID=IDS_TITLE_NEW;
}

UnitDlgNew::~UnitDlgNew()
{
}

void UnitDlgNew::ReloadCmbCat()
{
	CbReload(IDC_CMB_CAT, "select id, name from unit_cat order by name", -1, m_oidCat);
}

void UnitDlgNew::OnCbnSelChangeCmbCat()
{
	m_oidCat=CbGetOid(IDC_CMB_CAT);
	ReloadCmbUnit();
}

void UnitDlgNew::OnBnClickedBtnCat()
{
	UnitCatDlgNew dlg;
	if(dlg.DoModal()==IDOK)
	{
		m_oidCat=dlg.GetObjID();
		ReloadCmbCat();
		ReloadCmbUnit();
	}
}

BOOL UnitDlgNew::OnInitDialog()
{
	UnitDlg::OnInitDialog();
	ReloadCmbCat();
	return TRUE;
}

void UnitDlgNew::OnOK()
{
	ValidStr cstrName;
	GetDlgItemText(IDC_EDT_NAME, cstrName);
	if(!cstrName.IsValidName())
	{
		ShowInfo(IDC_EDT_NAME, IDS_BAD_TEXT);
		return;
	}

	if(m_oidCat==0)
	{
		ShowInfo(IDC_CMB_CAT, IDS_BAD_SELECT);
		return;
	}

	ValidStr cstrRatio;
	GetDlgItemText(IDC_EDT_RATIO, cstrRatio);
	if(!cstrRatio.IsValidNumber() || _tstof(cstrRatio)==0)
	{
		ShowInfo(IDC_EDT_RATIO, IDS_BAD_TEXT);
		return;
	}

	OBJID oidUnitRatio=CbGetOid(IDC_CMB_UNIT);
	if(oidUnitRatio==0)
	{
		ShowInfo(IDC_CMB_UNIT, IDS_BAD_SELECT);
		return;
	}

	StringA stra;
	stra.Format("insert into unit(name, ucid, ratio) values('%s', %u, (%s)*(%f))"
		, WcharToUtf8(cstrName)
		, m_oidCat
		, WcharToUtf8(cstrRatio)
		, GetUnitRatio(oidUnitRatio));

	m_oid=theApp.Insert(stra, this);
	if(m_oid==0)
		return;

	m_rm.SetModified(ReloadMgr::oprNew);

	UnitDlg::OnOK();
}
