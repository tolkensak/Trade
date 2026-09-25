
#include "stdafx.h"
#include "App.h"
#include "WareDlg.h"
#include "WareCatDlgNew.h"
#include "UnitCatDlgNew.h"
#include "FirmDlgNew.h"


BEGIN_MESSAGE_MAP(WareDlg, ManipDlg)
	ON_CBN_SELCHANGE(IDC_CMB_WARE_CAT, &WareDlg::OnCbnSelChangeCmbWareCat)
	ON_BN_CLICKED(IDC_BTN_WARE_CAT, &WareDlg::OnBnClickedBtnWareCat)
	ON_CBN_SELCHANGE(IDC_CMB_FIRM, &WareDlg::OnCbnSelChangeCmbFirm)
	ON_BN_CLICKED(IDC_BTN_FIRM, &WareDlg::OnBnClickedBtnFirm)
	ON_CBN_SELCHANGE(IDC_CMB_UNIT_CAT, &WareDlg::OnCbnSelChangeCmbUnitCat)
	ON_BN_CLICKED(IDC_BTN_UNIT_CAT, &WareDlg::OnBnClickedBtnUnitCat)
END_MESSAGE_MAP()


WareDlg::WareDlg(OBJID oidWare, CWnd* pParent /*=NULL*/)
	: ManipDlg(WareDlg::IDD, oidWare, pParent)
	, m_oidWareCat(0)
	, m_oidUnitCat(0)
	, m_oidFirm(0)
{
	m_rm.SetObject(ReloadMgr::objWare);
}

WareDlg::~WareDlg()
{
}

void WareDlg::ReloadCmbWareCat()
{
	CbReload(IDC_CMB_WARE_CAT, "select id, name from ware_cat order by name", -1, m_oidWareCat);
}

void WareDlg::ReloadCmbUnitCat()
{
	CbReload(IDC_CMB_UNIT_CAT, "select id, name from unit_cat order by name", -1, m_oidUnitCat);
}

void WareDlg::ReloadCmbFirm()
{
}

BOOL WareDlg::OnInitDialog()
{
	ManipDlg::OnInitDialog();
	ReloadCmbWareCat();
	ReloadCmbUnitCat();
	ReloadCmbFirm();
	return TRUE;
}

void WareDlg::OnCbnSelChangeCmbWareCat()
{
	m_oidWareCat=CbGetOid(IDC_CMB_WARE_CAT);
}

void WareDlg::OnCbnSelChangeCmbFirm()
{
	m_oidFirm=CbGetOid(IDC_CMB_FIRM);
}

void WareDlg::OnCbnSelChangeCmbUnitCat()
{
	m_oidUnitCat=CbGetOid(IDC_CMB_UNIT_CAT);
}

void WareDlg::OnBnClickedBtnUnitCat()
{
	UnitCatDlgNew dlg;
	if(dlg.DoModal()==IDOK)
	{
		m_oidUnitCat=dlg.GetObjID();
		ReloadCmbUnitCat();
	}
}

void WareDlg::OnBnClickedBtnWareCat()
{
	WareCatDlgNew dlg;
	if(dlg.DoModal()==IDOK)
	{
		m_oidWareCat=dlg.GetObjID();
		ReloadCmbWareCat();
	}
}

void WareDlg::OnBnClickedBtnFirm()
{
	FirmDlgNew dlg;
	if(dlg.DoModal()==IDOK)
	{
		m_oidFirm=dlg.GetObjID();
		ReloadCmbFirm();
	}
}

BOOL WareDlg::IsValid(ValidStr& cstrName)
{
	GetDlgItemText(IDC_EDT_NAME, cstrName);
	if(!cstrName.IsValidName())
	{
		ShowInfo(IDC_EDT_NAME, IDS_BAD_TEXT);
		return FALSE;
	}

	if(m_oidWareCat==0)
	{
		ShowInfo(IDC_CMB_WARE_CAT, IDS_BAD_SELECT);
		return FALSE;
	}

	if(m_oidFirm==0)
	{
		ShowInfo(IDC_CMB_FIRM, IDS_BAD_SELECT);
		return FALSE;
	}

	return TRUE;
}
