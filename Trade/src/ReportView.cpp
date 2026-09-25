
#include "stdafx.h"
#include "App.h"
#include "ReportView.h"
#include "ReportDlgSpec.h"
#include "Report.h"


IMPLEMENT_DYNCREATE(ReportView, TableView)

BEGIN_MESSAGE_MAP(ReportView, TableView)
	ON_COMMAND(ID_DATA_EDIT, &ReportView::OnDataEdit)
	ON_COMMAND(ID_DATA_VIEW, &ReportView::OnDataView)
	ON_COMMAND(ID_DATA_EXPORT, &ReportView::OnDataExport)
	ON_UPDATE_COMMAND_UI(ID_DATA_VIEW, &ReportView::OnUpdateDataView)
	ON_UPDATE_COMMAND_UI(ID_DATA_EXPORT, &ReportView::OnUpdateDataExport)
	ON_COMMAND(ID_DATA_NEW, &ReportView::OnDataNew)
	ON_COMMAND(ID_DATA_DELETE, &ReportView::OnDataDelete)
	ON_UPDATE_COMMAND_UI(ID_DATA_DELETE, &ReportView::OnUpdateDataDelete)
END_MESSAGE_MAP()


ReportView::ReportView()
	: TableView(IDR_REPORT)
{
	m_straReload="call sp_report_list()";

	int i=0;
	m_arrColumn.Add(Column(IDS_COL_NAME, Column::typeText, 140, i++));
}

ReportView::~ReportView()
{
}

BOOL ReportView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style|=LVS_SINGLESEL;
	return TableView::PreCreateWindow(cs);
}

BOOL ReportView::ContextMenu(HMENU hMenu, UINT* puFlags, int iItem)
{
	HMENU hMenuMain=AfxGetMainWnd()->GetMenu()->GetSafeHmenu();
	if(!hMenuMain)
		return FALSE;

	Menu_CopyItem(hMenu, -1, hMenuMain, ID_DATA_VIEW, TRUE);

	return TRUE;
}

void ReportView::DblClkItem(int nItem)
{
	MakeReport(GetItemObjID(nItem));
}

void ReportView::Reload()
{
	TableView::Reload();

	CListCtrl& lc=GetListCtrl();
	int n=lc.GetItemCount();
	if(n==0)
		return;

	CString str;
	if(!GetReportDir(str))
		return;

	PathAppend(str.GetBuffer(MAX_PATH), _T("report.xml"));
	str.ReleaseBuffer();

	XmlDoc xml;
	if(!xml.Open(str))
		return;

	xml.GetDocPtr()->setProperty((bstr_t)"SelectionLanguage", (_variant_t)"XPath");
	str.Format(_T("lang[@id='%u']"), theApp.GetLangID());
	MSXML2::IXMLDOMNodePtr nodePtrLang=xml.GetDocPtr()->documentElement->selectSingleNode((_bstr_t)str);
	if(!nodePtrLang)
		return;

	MSXML2::IXMLDOMNodePtr nodePtr;

	LVITEM lvi;
	lvi.iSubItem=0;

	for(lvi.iItem=0; lvi.iItem<n; lvi.iItem++)
	{
		lvi.mask=LVIF_PARAM;
		lc.GetItem(&lvi);

		str.Format(_T("report[@id='%u']"), (OBJID)lvi.lParam);
		nodePtr=nodePtrLang->selectSingleNode((_bstr_t)str);
		if(nodePtr)
		{
			lvi.mask=LVIF_TEXT;
			lvi.pszText=nodePtr->text;
			lc.SetItem(&lvi);
		}
	}
}

void ReportView::MakeReport(OBJID oidReport)
{
	if(oidReport==0)
		return;

	ReportDlgSpec dlg(oidReport);
	dlg.DoModal();
}

void ReportView::OnDataEdit()
{
	MakeReport(GetFirstSelectedItemObjID());
}

void ReportView::OnDataView()
{
	MakeReport(GetFirstSelectedItemObjID());
}

void ReportView::OnDataExport()
{
}

void ReportView::OnUpdateDataView(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetListCtrl().GetSelectedCount()==1);
}

void ReportView::OnUpdateDataExport(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetListCtrl().GetSelectedCount()==1);
}

void ReportView::OnDataNew()
{
}

void ReportView::OnDataDelete()
{
}

void ReportView::OnUpdateDataDelete(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(FALSE);
}
