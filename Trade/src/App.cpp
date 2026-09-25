
#include "stdafx.h"
#include "App.h"
#include "MainWnd.h"
#include "Doc.h"
#include "LoginDlg.h"
#include "MyPasswordDlg.h"
#include "ConnectionDlg.h"

#include "MainView.h"
#include "WareView.h"
#include "WareCatView.h"
#include "UnitView.h"
#include "UnitCatView.h"
#include "UserView.h"
#include "SellView.h"
#include "BuyView.h"
#include "FirmView.h"
#include "ClientView.h"
#include "IndentView.h"
#include "ReportView.h"
#include "ReportDlgGlob.h"

#include "Report.h" // TempFiles


//#define MYSQLDB "sawda1try"
#define MYSQLDB "sawda1"


BEGIN_MESSAGE_MAP(App, TSDIMVWinAppLang)
	ON_COMMAND(ID_DATA_MY_PASSWORD, &App::OnDataMyPassword)
	ON_COMMAND(ID_DATA_REPORT, &App::OnDataReport)
	ON_COMMAND(ID_DELETE_TEMP_FILE, &App::OnDeleteTempFile)
END_MESSAGE_MAP()


App::App()
{
	m_uStartedTimes=1;
}

App::~App()
{
#ifndef REPORT_COPY_TO_TEMP
	DeleteTempFiles();
#endif
}


App theApp;	// The one and only App object


BOOL App::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize=sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use in your application.
	InitCtrls.dwICC=ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CoInitialize(NULL);

	if(!TSDIMVWinAppLang::InitInstance())
		return FALSE;

#ifdef REPORT_COPY_TO_TEMP
	CleanTempFiles();
#endif

	if(MySQL::LibraryInit())
		return FALSE;

	LoginDlg dlg;
	if(dlg.DoModal()!=IDOK)
		return FALSE;

	m_permit.Reload();


	AddDocTemplate(IDR_MAIN, RUNTIME_CLASS(MainView));

	if(CheckPermit(ID_PERMIT_SELL))
		AddDocTemplate(IDR_SELL, RUNTIME_CLASS(SellView));

	if(CheckPermit(ID_PERMIT_INDENT))
		AddDocTemplate(IDR_INDENT, RUNTIME_CLASS(IndentView));

	if(CheckPermit(ID_PERMIT_BUY))
		AddDocTemplate(IDR_BUY, RUNTIME_CLASS(BuyView));

	if(CheckPermit(ID_PERMIT_LIST_WARE))
		AddDocTemplate(IDR_WARE_CAT, RUNTIME_CLASS(WareCatView));

	if(CheckPermit(ID_PERMIT_LIST_WARE))
		AddDocTemplate(IDR_WARE, RUNTIME_CLASS(WareView));

	if(CheckPermit(ID_PERMIT_LIST_UNIT))
		AddDocTemplate(IDR_UNIT_CAT, RUNTIME_CLASS(UnitCatView));

	if(CheckPermit(ID_PERMIT_LIST_UNIT))
		AddDocTemplate(IDR_UNIT, RUNTIME_CLASS(UnitView));

	if(CheckPermit(ID_PERMIT_LIST_CLIENT))
		AddDocTemplate(IDR_CLIENT, RUNTIME_CLASS(ClientView));

	if(CheckPermit(ID_PERMIT_LIST_FIRM))
		AddDocTemplate(IDR_FIRM, RUNTIME_CLASS(FirmView));

	if(CheckPermit(ID_PERMIT_LIST_USER))
		AddDocTemplate(IDR_USER, RUNTIME_CLASS(UserView));

	if(CheckPermit(ID_PERMIT_REPORT))
		AddDocTemplate(IDR_REPORT, RUNTIME_CLASS(ReportView));


	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line.  Will return FALSE if app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if(!ProcessShellCommand(cmdInfo))
		return FALSE;

	m_pMainWnd->SendMessage(WM_COMMAND, MAKEWPARAM(GetDeskCmdID(m_user.GetDesk()), 0));

	// The one and only window has been initialized, so show and update it
	m_pMainWnd->ShowWindow(m_uStartedTimes==1?SW_SHOWNORMAL:m_nCmdShow);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

int App::ExitInstance()
{
	m_user.Save();

	m_conn.Close();
	MySQL::LibraryEnd();

	CoUninitialize();
	return TSDIMVWinAppLang::ExitInstance();
}

void App::AddDocTemplate(UINT uResID, CRuntimeClass* pViewClass)
{
	ASSERT(uResID);
	ASSERT(pViewClass);

	TSDIMVWinAppLang::AddDocTemplate(
		new TSDIMVDocTemplate(
			uResID,
			RUNTIME_CLASS(Doc),
			RUNTIME_CLASS(MainWnd),
			pViewClass));
}

void App::CreateDeskMenu(HMENU hMenuParent)
{
	if(!hMenuParent)
		return;

	HMENU hMenu=GetSubMenu(hMenuParent, 0);
	if(!hMenu)
		return;

	UINT uResID;
	UINT uCmdID;
	CString str;
	TSDIMVDocTemplate* pTemplate;
	UINT uNewResID=GetUser().GetDesk();

	int i=0;
	POSITION pos=GetFirstDocTemplatePosition();

	while(pos)
	{
		pTemplate=(TSDIMVDocTemplate*)GetNextDocTemplate(pos);

		//if(i==1)
		//	if(InsertMenu(hMenu, i, MF_SEPARATOR|MF_BYPOSITION, 0, 0))
		//		i++;

		uResID=pTemplate->GetResourceID();
		if(uResID==IDR_MAIN)
			continue;

		uCmdID=GetDeskCmdID(uResID);

		str.LoadString(uResID);
		if(InsertMenu(hMenu, i, (uResID==uNewResID?MF_CHECKED:MF_UNCHECKED)|MF_STRING|MF_BYPOSITION, uCmdID, str.Left(str.Find(_T('\n')))))
			i++;
	}

	if(i)
		InsertMenu(hMenu, i, MF_SEPARATOR|MF_BYPOSITION, 0, 0);
}

const Connection& App::Connect() const
{
	App* pApp=const_cast<App*>(this);

	if(pApp->m_conn && pApp->m_conn.Ping()==0)
		return m_conn;

	pApp->m_conn.Close();

	if(!pApp->m_conn.Init())
	{
		AfxMessageBox(_T("Can't init connection to MySQL"));
		return m_conn;
	}

	StringA straHost;
	ConnectionDlg::GetHost(straHost);

	my_bool b=1;
	pApp->m_conn.Options(MYSQL_OPT_RECONNECT, &b);

	if(!pApp->m_conn.RealConnect(straHost, "sawda", "oS4hn4%shG^62Ak", MYSQLDB, 0, 0, CLIENT_MULTI_STATEMENTS|CLIENT_MULTI_RESULTS))
	{
		AfxMessageBox(_T("Can't connect to MySQL"));
		return m_conn;
	}

	pApp->m_conn.SetCharacterSet("utf8");
	return m_conn;
}

BOOL App::Exec(const StringA& stra, CWnd* pParent) const
{
	ASSERT(!stra.IsEmpty());

	const Connection& conn=Connect();
	if(!conn)
		return FALSE;

	if(conn.RealQuery((PCCharA)stra, stra.Len()))
	{
		conn.ShowError(pParent);
		return FALSE;
	}

	return TRUE;
}

OBJID App::Insert(const StringA& stra, CWnd* pParent) const
{
	ASSERT(!stra.IsEmpty());

	const Connection& conn=Connect();
	if(!conn)
		return 0;

	if(conn.RealQuery((PCCharA)stra, stra.Len()))
	{
		conn.ShowError(pParent);
		return 0;
	}

	return conn.GetNewObjID();
}

MySQLResPtr App::Query(const StringA& stra, CWnd* pParent, BOOL bUseResult) const
{
	ASSERT(!stra.IsEmpty());

	const Connection& conn=Connect();
	if(!conn)
		return NULL;

	if(conn.RealQuery((PCCharA)stra, stra.Len()))
	{
		conn.ShowError(pParent);
		return NULL;
	}

	MySQLResPtr pRes=bUseResult?conn.UseResult():conn.StoreResult();
	if(!pRes)
	{
		conn.ShowError(pParent);
		return NULL;
	}

	return pRes;
}

//void App::NextResult(MySQLResPtr& pRes) const
//{
//	if(!pRes)
//		return;
//
//	pRes->FreeResult();
//
//	if(!m_conn)
//		return;
//
//	if(m_conn.NextResult())
//	{
//		m_conn.ShowError();
//		return;
//	}
//
//	pRes=m_conn.StoreResult();
//	if(!pRes)
//		m_conn.ShowError();
//}

BOOL App::CheckPermit(OBJID oidPermit) const
{
	return (m_user.GetPermit()&m_permit.GetFlag(oidPermit));
}

//BOOL App::CheckPermit(const CUIntArray& arrPermitID) const
//{
//	for(int i=arrPermitID.GetCount()-1; i>=0; i--)
//		if((m_user.GetPermit()&m_permit.GetFlag(arrPermitID[i]))
//			return TRUE;
//
//	return FALSE;
//}

void App::OnDataMyPassword()
{
	MyPasswordDlg dlg;
	dlg.DoModal();
}

void App::OnDataReport()
{
	ReportDlgGlob dlg;
	dlg.DoModal();
}

void App::OnDeleteTempFile()
{
	DeleteTempFiles();
}

void App::AddLangMenu(HMENU hMenu)
{
	Lang_Menu(m_tLang, GetSubMenu(hMenu, 2), 0, ID_LANG_1, NULL, 0);
	CreateDeskMenu(hMenu);
}

BOOL App::PreTranslateMessage(MSG* pMsg)
{
	static BOOL bDecimalKeyDown=FALSE;

	if(pMsg->message==WM_KEYDOWN)
		bDecimalKeyDown=(pMsg->wParam==0x6e); // numpad decimal

	if(pMsg->message==WM_CHAR && bDecimalKeyDown)
		pMsg->wParam=0x2e; // period

	return TSDIMVWinAppLang::PreTranslateMessage(pMsg);
}
