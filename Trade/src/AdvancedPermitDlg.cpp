
#include "stdafx.h"
#include "App.h"
#include "AdvancedPermitDlg.h"


BEGIN_MESSAGE_MAP(AdvancedPermitDlg, PermitDlg)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, &AdvancedPermitDlg::OnLvnItemChangedList)
END_MESSAGE_MAP()


AdvancedPermitDlg::AdvancedPermitDlg(OBJID oidUser, CWnd* pParent /*=NULL*/)
	: PermitDlg(AdvancedPermitDlg::IDD, oidUser, pParent)
{
}

AdvancedPermitDlg::~AdvancedPermitDlg()
{
}

BOOL AdvancedPermitDlg::OnInitDialog()
{
	PermitDlg::OnInitDialog();

	CListCtrl* pList=(CListCtrl*)GetDlgItem(IDC_LIST);

	TCHAR pch[TOL_MAXSTR];
	LVITEM lvi;
	lvi.mask=LVIF_TEXT|LVIF_PARAM;
	lvi.pszText=pch;
	lvi.iItem=0;
	lvi.iSubItem=0;

	HINSTANCE hInst=AfxGetResourceHandle();
	const Permit::ItemArray& arr=theApp.GetPermit().GetArray();
	const Permit::Item* ppi;
	int j;

	int n=arr.GetCount();
	for(int i=0; i<n; i++)
	{
		ppi=&arr[i];
		if(!LoadString(hInst, ppi->GetID(), pch, TOL_MAXSTR))
			pch[0]=_T('\0');

		lvi.lParam=ppi->GetFlag();
		j=pList->InsertItem(&lvi);
		if(j!=-1)
			lvi.iItem=j+1;
	}

	return TRUE;
}

void AdvancedPermitDlg::UpdateCheckState()
{
	m_bCheckStateChangable=FALSE;

	CListCtrl* pList=(CListCtrl*)GetDlgItem(IDC_LIST);
	int i=pList->GetItemCount();

	for(i--; i>=0; i--)
		pList->SetItemState(i, (m_dwPermit&pList->GetItemData(i))?INDEXTOSTATEIMAGEMASK(2):INDEXTOSTATEIMAGEMASK(1), LVIS_STATEIMAGEMASK);

	m_bCheckStateChangable=TRUE;
}

void AdvancedPermitDlg::OnLvnItemChangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pnmlv=reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	if(m_bCheckStateChangable && pnmlv->uChanged&LVIF_STATE)
	{
		if(pnmlv->uNewState&INDEXTOSTATEIMAGEMASK(2))
			m_dwPermit|=pnmlv->lParam;
		else
			m_dwPermit&=~pnmlv->lParam;
	}

	*pResult=0;
}
