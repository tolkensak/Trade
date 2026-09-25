
#include "stdafx.h"
#include "App.h"
#include "ChooseWareDlg.h"


BEGIN_MESSAGE_MAP(ChooseWareDlg, Dialog)
	ON_EN_CHANGE(IDC_EDT_WARE, &ChooseWareDlg::OnEnChangeEdtWare)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, &ChooseWareDlg::OnLvnItemChangedList)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, &ChooseWareDlg::OnNMDblClkList)
END_MESSAGE_MAP()


ChooseWareDlg::ChooseWareDlg(LPCTSTR pcInit, CWnd* pParent /*=NULL*/)
	: Dialog(ChooseWareDlg::IDD, pParent)
	, m_strInit(pcInit)
	, m_oid(0)
{
}

ChooseWareDlg::~ChooseWareDlg()
{
}

BOOL ChooseWareDlg::OnInitDialog()
{
	Dialog::OnInitDialog();

	m_edit.SubclassDlgItem(IDC_EDT_WARE, this);
	m_list.SubclassDlgItem(IDC_LIST, this);

	m_edit.SetWindowText(m_strInit);

	return TRUE;
}

void ChooseWareDlg::OnEnChangeEdtWare()
{
	CString cstr;
	m_edit.GetWindowText(cstr);
	m_list.Reload(cstr);
}

void ChooseWareDlg::OnLvnItemChangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pnmlv=reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	if((pnmlv->uChanged&LVIF_STATE))
		m_oid=(pnmlv->uNewState&LVIS_SELECTED)?(OBJID)pnmlv->lParam:0;

	*pResult=0;
}

void ChooseWareDlg::OnNMDblClkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pnmia=reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	if(pnmia->iItem!=-1)
	{
		m_oid=(OBJID)m_list.GetItemData(pnmia->iItem);
		Dialog::OnOK();
	}

	*pResult=0;
}

void ChooseWareDlg::OnOK()
{
	if(m_oid==0)
	{
		ShowInfo(IDC_EDT_WARE, IDS_BAD_SELECT);
		return;
	}

	Dialog::OnOK();
}
