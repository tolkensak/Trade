
#include "stdafx.h"
#include "App.h"
#include "GridDlg.h"
#include "FormatStr.h"


GridDlg::Data::Data()
	: oidUser(0)
{
}

GridDlg::Data::~Data()
{
}


BEGIN_MESSAGE_MAP(GridDlg, TableDlg)
	ON_BN_CLICKED(IDC_BTN_APPLY, &GridDlg::OnBnClickedBtnApply)
END_MESSAGE_MAP()


GridDlg::GridDlg(UINT uIDTemplate, CWnd* pParent /*=NULL*/)
	: TableDlg(uIDTemplate, pParent)
{
}

GridDlg::~GridDlg()
{
}

BOOL GridDlg::OnInitDialog()
{
	TableDlg::OnInitDialog();

	CListCtrl* pList=(CListCtrl*)GetDlgItem(IDC_LIST);

	DWORD dwStyle=GetWindowLongPtr(pList->GetSafeHwnd(), GWL_STYLE);
	dwStyle&=~LVS_NOCOLUMNHEADER;
	SetWindowLongPtr(pList->GetSafeHwnd(), GWL_STYLE, dwStyle|LVS_REPORT|LVS_SHOWSELALWAYS);

	pList->SetExtendedStyle(LVS_EX_CHECKBOXES|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	LayColumn();
	Reload();

	return TRUE;
}

BOOL GridDlg::LayColumn()
{
	int i;
	CListCtrl* pList=(CListCtrl*)GetDlgItem(IDC_LIST);
	CHeaderCtrl* pHeader=pList->GetHeaderCtrl();

	for(i=pHeader->GetItemCount()-1; i>=0; i--)
		pList->DeleteColumn(i);

	CString str;
	const Column* pCol;

	HDITEM hdi;
	hdi.mask=HDI_LPARAM;//|HDI_TEXT|HDI_WIDTH|HDI_FORMAT;

	int n=m_arrColumn.GetCount();

	for(i=0; i<n; i++)
	{
		pCol=&m_arrColumn[i];
		str.LoadString(pCol->GetStrID());

		pList->InsertColumn(i, str, pCol->GetFormat(), pCol->GetWidth(), pCol->GetSubItem());

		//hdi.pszText=str.GetBuffer();
		//hdi.cxy=pCol->GetWidth();
		//hdi.fmt=pCol->GetFormat();
		hdi.lParam=pCol->GetType();
		pHeader->SetItem(i, &hdi);
		//str.ReleaseBuffer();
	}

	return TRUE;
}

void GridDlg::Reload()
{
	static TCHAR pch[TOL_MAXSTR];

	CListCtrl* pList=(CListCtrl*)GetDlgItem(IDC_LIST);
	pList->DeleteAllItems();

	if(m_straReload.IsEmpty())
		return;

	MySQLResPtr pRes=theApp.Query(m_straReload, this, TRUE);
	if(!pRes)
		return;

	CHeaderCtrl* pHeader=pList->GetHeaderCtrl();
	COleDateTime datetime;
	HDITEM hdi;
	hdi.mask=HDI_LPARAM;

	LVITEM lvi;
	lvi.mask=LVIF_TEXT;
	lvi.pszText=pch;
	lvi.iItem=0;

	int i=pRes->NumFields();
	int nCol=pHeader->GetItemCount();
	if(nCol>i)
		nCol=i;

	PULONG len;
	MYSQL_ROW row;
	DataPtr pData;

	CString cstrYes;
	cstrYes.LoadString(IDYES);

	FormatStr fmtDT(FormatStr::typeLoad, FormatStr::partDateTime);
	FormatStr fmtD(FormatStr::typeLoad, FormatStr::partDate);
	FormatStr fmtT(FormatStr::typeLoad, FormatStr::partTime);

	while(row=pRes->FetchRow())
	{
		len=pRes->FetchLengths();

		for(lvi.iSubItem=0; lvi.iSubItem<nCol; lvi.iSubItem++)
		{
			if(!row[lvi.iSubItem])
				continue;

			pHeader->GetItem(lvi.iSubItem, &hdi);

			if(hdi.lParam==Column::typeBoolean)
			{
				if(atoi(row[lvi.iSubItem]))
					lstrcpy(pch, cstrYes);
				else
					pch[0]=_T('\0');
			}
			else
			{
				Utf8ToWchar(row[lvi.iSubItem], len[lvi.iSubItem], pch);

				if(hdi.lParam==Column::typeDateTime)
				{
					datetime.ParseDateTime(pch);
					lstrcpy(pch, datetime.Format(fmtDT));
				}
				else if(hdi.lParam==Column::typeDate)
				{
					datetime.ParseDateTime(pch);
					lstrcpy(pch, datetime.Format(fmtD));
				}
				else if(hdi.lParam==Column::typeTime)
				{
					datetime.ParseDateTime(pch);
					lstrcpy(pch, datetime.Format(fmtT));
				}
			}

			if(lvi.iSubItem)
				pList->SetItem(&lvi);
			else
			{
				pData=new Data;
				pData->oidUser=atoi(row[nCol]);
				pData->straMoment=row[nCol+1];

				lvi.mask|=LVIF_PARAM;
				lvi.lParam=m_arrData.Add(pData);
				i=pList->InsertItem(&lvi);
				lvi.mask&=~LVIF_PARAM;

				if(i==-1)
					break;

				lvi.iItem=i;
			}
		}

		lvi.iItem++;
	}
}

void GridDlg::GetApplyStr(StringA& stra)
{
	stra.Empty();

	DataPtr pData;
	StringA straWhere;
	CListCtrl* pList=(CListCtrl*)GetDlgItem(IDC_LIST);

	for(int i=pList->GetItemCount()-1; i>=0; i--)
		if(pList->GetItemState(i, LVIS_STATEIMAGEMASK)==INDEXTOSTATEIMAGEMASK(2))
		{
			pData=m_arrData.GetAt(pList->GetItemData(i));

			if(!straWhere.IsEmpty())
				straWhere+=" || ";

			straWhere.FormatCat(" (uid=%u && moment='%s') ", pData->oidUser, (PCCharA)pData->straMoment);
		}

	if(!straWhere.IsEmpty())
		stra.Format(m_straFormatApply, (PCCharA)straWhere);
}

int GridDlg::Apply(UINT uMsgBtns)
{
	StringA stra;
	GetApplyStr(stra);

	if(stra.IsEmpty())
		return 0;

	int nRet=MsgBox(this, MB_ICONQUESTION|uMsgBtns, IDS_PROMPT_APPLY);
	if(nRet==IDCANCEL)
		return IDCANCEL;

	if(nRet==IDNO)
		return IDNO;

	if(theApp.Exec(stra, this))
		return IDYES;

	return 0;
}

void GridDlg::OnBnClickedBtnApply()
{
	if(Apply(MB_YESNO)==IDYES)
		Reload();
}

void GridDlg::OnOK()
{
	switch(Apply(MB_YESNOCANCEL))
	{
	case IDYES:
		TableDlg::OnOK();
		break;

	case IDNO:
		TableDlg::OnCancel();
		break;
	}
}
