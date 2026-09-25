
#include "stdafx.h"
#include "App.h"
#include "ConnectionDlg.h"


BEGIN_MESSAGE_MAP(ConnectionDlg, Dialog)
END_MESSAGE_MAP()


ConnectionDlg::ConnectionDlg(CWnd* pParent /*=NULL*/)
	: Dialog(ConnectionDlg::IDD, pParent)
{
	m_uTitleFormatID=IDS_TITLE_CHANGE;
}

ConnectionDlg::~ConnectionDlg()
{
}

BOOL ConnectionDlg::OnInitDialog()
{
	Dialog::OnInitDialog();

	GetHost(m_strHostOrg);
	SetDlgItemText(IDC_EDT_HOST, m_strHostOrg);

	return TRUE;
}

void ConnectionDlg::OnOK()
{
	CString str;
	GetDlgItemText(IDC_EDT_HOST, str);

	if(str!=m_strHostOrg)
		theApp.WriteProfileString(_T("Connection"), _T("Host"), str);

	Dialog::OnOK();
}

void ConnectionDlg::GetHost(CString& cstr)
{
#ifdef UNICODE
	StringW str;
#else
	Stringa str;
#endif

	GetHost(str);
	cstr=str;
}

void ConnectionDlg::GetHost(StringW& strw)
{
#ifdef UNICODE
	strw=theApp.GetProfileString(_T("Connection"), _T("Host"));
#else
	Stringa stra;
	GetHost(stra);
	strw.Copy((PCCharA)stra, stra.Len());
#endif
}

void ConnectionDlg::GetHost(StringA& stra)
{
#ifdef UNICODE
	StringW strw;
	GetHost(strw);
	stra.Copy((PCCharW)strw, strw.Len());
#else
	stra=theApp.GetProfileString(_T("Connection"), _T("Host"));
#endif
}
