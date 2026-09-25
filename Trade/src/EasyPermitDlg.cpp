
#include "stdafx.h"
#include "App.h"
#include "EasyPermitDlg.h"


BEGIN_MESSAGE_MAP(EasyPermitDlg, PermitDlg)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, &EasyPermitDlg::OnLvnItemChangedList)
END_MESSAGE_MAP()


EasyPermitDlg::EasyPermitDlg(OBJID oidUser, CWnd* pParent /*=NULL*/)
	: PermitDlg(EasyPermitDlg::IDD, oidUser, pParent)
{
}

EasyPermitDlg::~EasyPermitDlg()
{
}

BOOL EasyPermitDlg::OnInitDialog()
{
	PermitDlg::OnInitDialog();

	CListCtrl* pList=(CListCtrl*)GetDlgItem(IDC_LIST);

	StringA stra;
	stra="call sp_role_list()";

	MySQLResPtr pRes=theApp.Query(stra, this, TRUE);
	if(!pRes)
		return TRUE;

	TCHAR pch[TOL_MAXSTR];
	LVITEM lvi;
	lvi.mask=LVIF_TEXT|LVIF_PARAM;
	lvi.pszText=pch;
	lvi.iItem=0;
	lvi.iSubItem=0;

	int i;
	MYSQL_ROW row;
	HINSTANCE hInst=AfxGetResourceHandle();

	while(row=pRes->FetchRow())
	{
		if(!LoadString(hInst, atoi(row[0])+IDS_ROLE, pch, TOL_MAXSTR))
			pch[0]=_T('\0');

		lvi.lParam=atol(row[1]);

		i=pList->InsertItem(&lvi);
		if(i!=-1)
			lvi.iItem=i+1;
	}

	if(!LoadString(hInst, IDS_ROLE, pch, TOL_MAXSTR))
		pch[0]=_T('\0');

	lvi.lParam=0;
	pList->InsertItem(&lvi);

	return TRUE;
}

void EasyPermitDlg::UpdateCheckState()
{
	m_bCheckStateChangable=FALSE;

	BOOL bMatch=FALSE;
	CListCtrl* pList=(CListCtrl*)GetDlgItem(IDC_LIST);

	int i;
	int n=pList->GetItemCount();

	for(i=0; i<n; i++)
	{
		if((pList->GetItemData(i)==m_dwPermit))
		{
			pList->SetItemState(i, INDEXTOSTATEIMAGEMASK(2), LVIS_STATEIMAGEMASK);

			if(!bMatch)
				bMatch=TRUE;
		}
		else
			pList->SetItemState(i, INDEXTOSTATEIMAGEMASK(1), LVIS_STATEIMAGEMASK);
	}

	if(!bMatch)
	{
		for(i=0; i<n; i++)
			if(pList->GetItemData(i)==0)
			{
				pList->SetItemState(i, INDEXTOSTATEIMAGEMASK(2), LVIS_STATEIMAGEMASK);
				break;
			}
	}

	m_bCheckStateChangable=TRUE;
}

void EasyPermitDlg::OnLvnItemChangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pnmlv=reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	if(m_bCheckStateChangable && pnmlv->uChanged&LVIF_STATE)
	{
		if(pnmlv->uNewState&INDEXTOSTATEIMAGEMASK(2))
		{
			CListCtrl* pList=(CListCtrl*)GetDlgItem(IDC_LIST);
			int i=pList->GetItemCount();
			for(i--; i>=0; i--)
				if(i!=pnmlv->iItem)
					pList->SetItemState(i, INDEXTOSTATEIMAGEMASK(1), LVIS_STATEIMAGEMASK);

			m_dwPermit=pnmlv->lParam;
		}
		else
			m_dwPermit=0;
	}

	*pResult=0;
}
