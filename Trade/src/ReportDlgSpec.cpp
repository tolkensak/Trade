
#include "stdafx.h"
#include "App.h"
#include "ReportDlgSpec.h"


BEGIN_MESSAGE_MAP(ReportDlgSpec, ReportDlg)
END_MESSAGE_MAP()


ReportDlgSpec::ReportDlgSpec(OBJID oidReport, CWnd* pParent /*=NULL*/)
	: ReportDlg(oidReport, pParent)
	, m_pForm(NULL)
{
}

ReportDlgSpec::~ReportDlgSpec()
{
}

BOOL CALLBACK DestroyChild(HWND hwnd, LPARAM lp)
{
	UINT uID=GetDlgCtrlID(hwnd);
	if(uID!=IDOK && uID!=IDCANCEL)
		DestroyWindow(hwnd);

	return TRUE;
}

BOOL CALLBACK MoveChild(HWND hwnd, LPARAM lp)
{
	CRect rc;
	GetWindowRect(hwnd, &rc);
	Rect_ScreenToClient(GetParent(hwnd), &rc);
	MoveWindow(hwnd, rc.left-((LPSIZE)lp)->cx, rc.top-((LPSIZE)lp)->cy, rc.Width(), rc.Height(), FALSE);

	return TRUE;
}

BOOL ReportDlgSpec::OnInitDialog()
{
	ReportDlg::OnInitDialog();

	EnumChildWindows(m_hWnd, DestroyChild, 0);


	StringA stra;
	stra.Format("select fid from report where id = %u", m_oidReport);

	MySQLResPtr pRes=theApp.Query(stra, this);
	if(!pRes)
		return TRUE;

	MYSQL_ROW row=pRes->FetchRow();
	if(!row)
		return TRUE;

	m_pForm=CreateForm(atoi(row[0]));
	if(!m_pForm)
		return TRUE;


	CRect rcDlg;
	GetWindowRect(&rcDlg);

	//CSize sz(rcDlg.Width(), 0);
	//if(sz.cx<350)
	//	sz.cx=350-sz.cx;
	//else if(sz.cx>450)
	//	sz.cx-=450;
	//else
	//	sz.cx=0;

	CSize sz(rcDlg.Width()-400, 0);
	if(sz.cx)
	{
		MoveWindow(rcDlg.left, rcDlg.top, rcDlg.Width()-sz.cx, rcDlg.Height()-sz.cy, FALSE);
		EnumChildWindows(m_hWnd, MoveChild, (LPARAM)&sz);
		GetWindowRect(&rcDlg);
		sz.cx=0;
	}

	double dx;
	double dy;
	GetDlgUnit(dx, dy);

	CRect rc;
	GetRectForForm(rc);
	sz.cy=rc.Height()-(m_pForm->GetHeight()+(int)(24*dy));

	if(sz.cy)
	{
		MoveWindow(rcDlg.left, rcDlg.top, rcDlg.Width()-sz.cx, rcDlg.Height()-sz.cy, FALSE);
		EnumChildWindows(m_hWnd, MoveChild, (LPARAM)&sz);
	}

	m_pForm->Place(&rc);
	m_pForm->Show();
	m_pForm->SetFocus();

	return FALSE;
}

ReportFormPtr ReportDlgSpec::GetActiveForm()
{
	return m_pForm;
}
