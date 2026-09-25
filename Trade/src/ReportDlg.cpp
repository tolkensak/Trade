
#include "stdafx.h"
#include "App.h"
#include "ReportDlg.h"
#include "Report.h"


BEGIN_MESSAGE_MAP(ReportDlg, TableDlg)
END_MESSAGE_MAP()


ReportDlg::ReportDlg(OBJID oidReport, CWnd* pParent /*=NULL*/)
	: TableDlg(ReportDlg::IDD, pParent)
	, m_uCtrlID(3001)
	, m_oidReport(oidReport)
{
	m_uTitleFormatID=IDS_TITLE_NEW;
}

ReportDlg::~ReportDlg()
{
}

BOOL ReportDlg::OnInitDialog()
{
	TableDlg::OnInitDialog();
	ReportParam::Init(this);
	return TRUE;
}

void ReportDlg::GetDlgUnit(double& dx, double& dy)
{
	CRect rc(0, 0, 1000, 1000);
	MapDialogRect(&rc);

	dx=rc.Width()/(double)1000;
	dy=rc.Height()/(double)1000;
}

void ReportDlg::GetRectForForm(CRect& rc)
{
	double dx;
	double dy;
	GetDlgUnit(dx, dy);

	GetClientRect(&rc);
	rc.DeflateRect((int)(12*dx), (int)(12*dy), (int)(14*dx), (int)(12*dy));
}

HWND ReportDlg::GetInsertAfter()
{
	return HWND_TOP;
}

ReportFormPtr ReportDlg::CreateForm(OBJID oidForm)
{
	if(!oidForm)
		return NULL;

	ReportFormPtr pForm=new ReportForm(oidForm);
	if(!pForm)
		return NULL;

	StringA stra;
	stra.Format("call sp_param_list(%u)", oidForm);

	MySQLResPtr pRes=theApp.Query(stra, this);
	if(!pRes)
		return NULL;

	XmlDoc xml;
	MSXML2::IXMLDOMNodePtr nodePtr;
	MSXML2::IXMLDOMNodePtr nodePtrLang=NULL;

	CString str;
	GetReportDir(str);
	PathAppend(str.GetBuffer(MAX_PATH), _T("param.xml"));
	str.ReleaseBuffer();

	if(xml.Open(str))
	{
		xml.GetDocPtr()->setProperty((bstr_t)"SelectionLanguage", (_variant_t)"XPath");
		str.Format(_T("lang[@id='%u']"), theApp.GetLangID());
		nodePtrLang=xml.GetDocPtr()->documentElement->selectSingleNode((_bstr_t)str);
	}

	PULONG len;
	MYSQL_ROW row;
	OBJID oidParam;
	TCHAR pch[TOL_MAXSTR];
	LPCTSTR pcLabel;

	UINT uNewCtrlID;
	ReportParamPtr pParam;
	HWND hWndInsertAfter=GetInsertAfter();

	while(row=pRes->FetchRow())
	{
		pcLabel=NULL;
		oidParam=atoi(row[0]);

		if(nodePtrLang)
		{
			str.Format(_T("param[@id='%u']"), oidParam);
			nodePtr=nodePtrLang->selectSingleNode((_bstr_t)str);
			if(nodePtr)
				pcLabel=nodePtr->text;
		}

		if(!pcLabel)
		{
			len=pRes->FetchLengths();
			Utf8ToWchar(row[1], len[1], pch);
			pcLabel=pch;
		}

		pParam=new ReportParam;
		uNewCtrlID=pParam->Create(atoi(row[2]), atoi(row[3]), pcLabel, row[4], row[5], this, m_uCtrlID);
		if(uNewCtrlID>m_uCtrlID)
		{
			pForm->Add(pParam, hWndInsertAfter);
			m_uCtrlID=uNewCtrlID;
		}
	}

	return pForm;
}

BOOL ReportDlg::CreateReport()
{
	ReportFormPtr pForm=GetActiveForm();
	if(!pForm)
		return FALSE;

	StringA straValue;
	if(!pForm->GetValue(straValue))
		return FALSE;

	StringA stra;

#ifdef REPORT_COPY_TO_TEMP
	stra.Format("call rp_report_form%u(%s, %u, %u)"
		, pForm->GetID()
		, (PCCharA)straValue
		, m_oidReport, theApp.GetLangID());
#else

	CString cstrReportURL;
	if(!GetReportURL(cstrReportURL))
		return FALSE;

	stra.Format("call rp_report_form%u(%s, %u, %u, '%s')"
		, pForm->GetID()
		, (PCCharA)straValue
		, m_oidReport, theApp.GetLangID()
		, WcharToUtf8(cstrReportURL));
#endif

	return Report_Create(m_oidReport, stra, this);
}

void ReportDlg::OnOK()
{
	if(!CreateReport())
		return;
}
