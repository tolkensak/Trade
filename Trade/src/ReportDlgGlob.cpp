
#include "stdafx.h"
#include "App.h"
#include "ReportDlgGlob.h"
#include "Report.h"


BEGIN_MESSAGE_MAP(ReportDlgGlob, ReportDlg)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, &ReportDlgGlob::OnNMDblClkList)
END_MESSAGE_MAP()


ReportDlgGlob::ReportDlgGlob(CWnd* pParent /*=NULL*/)
	: ReportDlg(0, pParent)
	, m_oidForm(0)
{
}

ReportDlgGlob::~ReportDlgGlob()
{
}

ReportFormPtr ReportDlgGlob::GetActiveForm()
{
	return m_mapForm[m_oidForm];
}

void ReportDlgGlob::GetRectForForm(CRect& rc)
{
	double dx;
	double dy;
	GetDlgUnit(dx, dy);

	CWnd* pwnd=GetDlgItem(IDC_STC_FORM);
	pwnd->GetClientRect(&rc);
	pwnd->MapWindowPoints(this, &rc);
	rc.DeflateRect((int)(12*dx), (int)(24*dy), (int)(14*dx), (int)(12*dy));
}

HWND ReportDlgGlob::GetInsertAfter()
{
	return ::GetDlgItem(m_hWnd, IDC_STC_FORM);
}

BOOL ReportDlgGlob::OnInitDialog()
{
	ReportDlg::OnInitDialog();

	CListCtrl* pList=(CListCtrl*)GetDlgItem(IDC_LIST);
	DWORD dwStyle=GetWindowLongPtr(pList->GetSafeHwnd(), GWL_STYLE);
	SetWindowLongPtr(pList->GetSafeHwnd(), GWL_STYLE, dwStyle|LVS_SINGLESEL|LVS_REPORT|LVS_SHOWSELALWAYS|LVS_NOCOLUMNHEADER);

	RECT rc;
	pList->GetClientRect(&rc);
	rc.right-=GetSystemMetrics(SM_CXVSCROLL);
	pList->InsertColumn(0, NULL, 0, rc.right, 0);

	GetDlgItem(IDC_STC_INFO)->SendMessage(WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT));


	StringA stra;
	stra="call sp_report_list()";

	MySQLResPtr pRes=theApp.Query(stra, this, TRUE);
	if(!pRes)
		return TRUE;

	XmlDoc xml;
	MSXML2::IXMLDOMNodePtr nodePtr;
	MSXML2::IXMLDOMNodePtr nodePtrLang=NULL;

	CString str;
	if(!GetReportDir(str))
		return TRUE;

	PathAppend(str.GetBuffer(MAX_PATH), _T("report.xml"));
	str.ReleaseBuffer();

	if(xml.Open(str))
	{
		xml.GetDocPtr()->setProperty((bstr_t)"SelectionLanguage", (_variant_t)"XPath");
		str.Format(_T("lang[@id='%u']"), theApp.GetLangID());
		nodePtrLang=xml.GetDocPtr()->documentElement->selectSingleNode((_bstr_t)str);
	}

	int i;
	PULONG len;
	MYSQL_ROW row;
	OBJID oidReport;
	TCHAR pch[TOL_MAXSTR];

	LVITEM lvi;
	lvi.mask=LVIF_TEXT|LVIF_PARAM;
	lvi.iItem=0;
	lvi.iSubItem=0;

	while(row=pRes->FetchRow())
	{
		lvi.pszText=NULL;
		oidReport=atoi(row[0]);

		if(nodePtrLang)
		{
			str.Format(_T("report[@id='%u']"), oidReport);
			nodePtr=nodePtrLang->selectSingleNode((_bstr_t)str);
			if(nodePtr)
				lvi.pszText=nodePtr->text;
		}

		if(!lvi.pszText)
		{
			len=pRes->FetchLengths();
			Utf8ToWchar(row[1], len[1], pch);
			lvi.pszText=pch;
		}

		lvi.lParam=MAKELPARAM(oidReport, atoi(row[2]));

		i=pList->InsertItem(&lvi);
		if(i!=-1)
			lvi.iItem=i+1;
	}

	return TRUE;
}

void ReportDlgGlob::ChangeReport(int nItem)
{
	CListCtrl* pList=(CListCtrl*)GetDlgItem(IDC_LIST);

	if(nItem==-1)
	{
		POSITION pos=pList->GetFirstSelectedItemPosition();
		if(!pos)
			return;

		nItem=pList->GetNextSelectedItem(pos);
		if(nItem==-1)
			return;
	}

	LPARAM lp=pList->GetItemData(nItem);
	if(lp==0)
		return;

	CString strReport=pList->GetItemText(nItem, 0);
	CString strFormat;
	if(!strFormat.LoadString(IDS_TITLE_FORM))
		strFormat=_T("Parameters of %s");

	CString str;
	str.Format(strFormat, strReport);
	SetDlgItemText(IDC_STC_FORM, str);

	m_oidReport=(OBJID)LOWORD(lp);
	ChangeForm((OBJID)HIWORD(lp));
}

void ReportDlgGlob::ChangeForm(OBJID oidForm)
{
	if(oidForm==m_oidForm)
		return;

	ReportFormPtr pForm;
	
	if(m_oidForm)
	{
		pForm=m_mapForm[m_oidForm];
		if(pForm)
			pForm->Show(FALSE);
	}

	if(oidForm)
	{
		pForm=m_mapForm[oidForm];
		if(!pForm)
		{
			pForm=CreateForm(oidForm);
			if(pForm)
			{
				m_mapForm[oidForm]=pForm;

				CRect rc;
				GetRectForForm(rc);
				pForm->Place(&rc);
			}
		}

		if(pForm)
			pForm->Show();
	}

	m_oidForm=oidForm;
}

void ReportDlgGlob::OnNMDblClkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pnmia=reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	if(pnmia->iItem!=-1)
		ChangeReport(pnmia->iItem);

	*pResult=0;
}

void ReportDlgGlob::OnOK()
{
	if(GetFocus()==GetDlgItem(IDC_LIST))
	{
		ChangeReport();
		return;
	}

	ReportDlg::OnOK();
}
