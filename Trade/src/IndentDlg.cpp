
#include "stdafx.h"
#include "App.h"
#include "IndentDlg.h"
#include "ClientDlgNew.h"
#include "FormatStr.h"


BEGIN_MESSAGE_MAP(IndentDlg, ManipDlg)
	ON_CBN_SELCHANGE(IDC_CMB_CLIENT, &IndentDlg::OnCbnSelChangeCmbClient)
	ON_BN_CLICKED(IDC_BTN_CLIENT, &IndentDlg::OnBnClickedBtnClient)
END_MESSAGE_MAP()


IndentDlg::IndentDlg(OBJID oidIndent, CWnd* pParent /*=NULL*/)
	: ManipDlg(IndentDlg::IDD, oidIndent, pParent)
	, m_oidClient(0)
{
	m_rm.SetObject(ReloadMgr::objIndent);
}

IndentDlg::~IndentDlg()
{
}

void IndentDlg::ReloadCmbClient()
{
}

void IndentDlg::OnCbnSelChangeCmbClient()
{
	m_oidClient=CbGetOid(IDC_CMB_CLIENT);
}

void IndentDlg::OnBnClickedBtnClient()
{
	ClientDlgNew dlg;
	if(dlg.DoModal()==IDOK)
	{
		m_oidClient=dlg.GetObjID();
		ReloadCmbClient();
	}
}

BOOL IndentDlg::OnInitDialog()
{
	ManipDlg::OnInitDialog();

	ReloadCmbClient();

	FormatStr fmtD(FormatStr::typeCtrl, FormatStr::partDate);
	((CDateTimeCtrl*)GetDlgItem(IDC_DATE_DELIVER))->SetFormat(fmtD);

	return TRUE;
}

BOOL IndentDlg::PrepareData()
{
	if(m_oidClient==0)
	{
		ShowInfo(IDC_CMB_CLIENT, IDS_BAD_SELECT);
		return FALSE;
	}

	COleDateTime date;
	((CDateTimeCtrl*)GetDlgItem(IDC_DATE_DELIVER))->GetTime(date);

	FormatStr fmtD(FormatStr::typeStore, FormatStr::partDate);
	m_strDeliver=date.Format(fmtD);

	return TRUE;
}
