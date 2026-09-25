
#include "stdafx.h"
#include "App.h"
#include "MainWnd.h"


static UINT _muIndicator[]=
{
	ID_SEPARATOR,	// status line indicator
	ID_SEPARATOR,
	ID_SEPARATOR,
};

static UINT _muImageCmd[]=
{
	ID_APP_ABOUT,
	GetDeskCmdID(IDR_WARE),
	GetDeskCmdID(IDR_UNIT),
	GetDeskCmdID(IDR_USER),
	ID_DATA_NEW,
	ID_DATA_EDIT,
	ID_DATA_DELETE,
	ID_DATA_PASSWORD,
	ID_DATA_PERMIT,
	ID_VIEW_RELOAD,
	GetDeskCmdID(IDR_SELL),
	GetDeskCmdID(IDR_BUY),
	ID_DATA_PRICE,
	ID_DATA_SUBMIT,
	GetDeskCmdID(IDR_CLIENT),
	GetDeskCmdID(IDR_FIRM),
	GetDeskCmdID(IDR_INDENT),
	ID_DATA_CONTACT,
	ID_DATA_FILL,
	ID_DATA_STOP_FILL,
	ID_DATA_VIEW,
	GetDeskCmdID(IDR_REPORT),
};

static int _nImageCmdCount=sizeof(_muImageCmd)/sizeof(UINT);


IMPLEMENT_DYNCREATE(MainWnd, TSDIMVMainWndLang)

BEGIN_MESSAGE_MAP(MainWnd, TSDIMVMainWndLang)
	ON_WM_CREATE()
	ON_COMMAND_RANGE(ID_DESK_FIRST, ID_DESK_LAST, &MainWnd::OnDesk)
	ON_MESSAGE(UM_SET_STATUS_PANE_TEXT, &MainWnd::OnSetStatusPaneText)
END_MESSAGE_MAP()


MainWnd::MainWnd()
	: m_wndToolbar(_muImageCmd, _nImageCmdCount)
{
	SetMenuStyle();

	// image cmd
	MenuOD_SetImageCmds(m_tMenu, _muImageCmd, _nImageCmdCount);

	int i, j;
	HICON hIcon;
	HIMAGELIST hIml;
	
	// image list
	for(i=0; i<s_nImageListCount; i++)
	{
		hIml=ImageList_Create(16, 16, ILC_COLOR32, 0, 0);

		for(j=0; j<_nImageCmdCount; j++)
		{
			hIcon=(HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ABOUT_REG+i+j*3), IMAGE_ICON, 0, 0, 0);
			ImageList_ReplaceIcon(hIml, -1, hIcon);
			DestroyIcon(hIcon);
		}

		MenuOD_SetImageList(m_tMenu, hIml, i);
		m_iml[i].Attach(hIml);
	}
}

MainWnd::~MainWnd()
{
}

int MainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if(TSDIMVMainWndLang::OnCreate(lpCreateStruct)==-1)
		return -1;

	if(!m_wndToolbar.CreateEx(this, TBSTYLE_FLAT|TBSTYLE_TRANSPARENT))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}

	CToolBarCtrl& tbc=m_wndToolbar.GetToolBarCtrl();
	tbc.SetImageList(m_iml);
	tbc.SetDisabledImageList(m_iml+1);
	tbc.SetHotImageList(m_iml+2);

	if(!m_wndToolbar.LoadToolBar(IDR_MAIN))
	{
		TRACE0("Failed to load toolbar\n");
		return -1;
	}

	if(!m_wndRebar.Create(this) || !m_wndRebar.AddBar(&m_wndToolbar, NULL, NULL, RBBS_NOGRIPPER))
	{
		TRACE0("Failed to create rebar\n");
		return -1;
	}

	if(!m_wndStatusBar.Create(this) || !m_wndStatusBar.SetIndicators(_muIndicator, sizeof(_muIndicator)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;
	}

	m_wndStatusBar.SetPaneInfo(0, 0, SBPS_STRETCH, 0);
	m_wndStatusBar.SetPaneInfo(STATUS_PANE_NUM, 0, SBPS_NORMAL, 90);
	m_wndStatusBar.SetPaneInfo(STATUS_PANE_SUM, 0, SBPS_NORMAL, 150);

	m_wndToolbar.SetBarStyle(m_wndToolbar.GetBarStyle()|CBRS_TOOLTIPS|CBRS_FLYBY);

	return 0;
}

void MainWnd::UpdateMenu(HMENU hMenu, UINT uResID)
{
	//theApp.CreateDeskMenu(hMenu, uResID);
}

void MainWnd::UpdateResource(TSDIMVDocTemplate *pNewTemplate)
{
	TSDIMVMainWndLang::UpdateResource(pNewTemplate);
	// load toolbar form template
	m_wndToolbar.LoadToolBar(pNewTemplate->GetResourceID());
}

void MainWnd::OnDesk(UINT uCmdID)
{
	UINT uOldResID=theApp.GetUser().GetDesk();

	UINT uResID=GetDeskResID(uCmdID);
	theApp.GetUser().SetDesk(uResID);

	if(ActivateView(uResID))
	{
		SetStatusPaneText(0, 0);
		GetActiveView()->SendMessage(UM_VIEW_ACTIVATED);
	}
	else
		theApp.GetUser().SetDesk(uOldResID);
}

LRESULT MainWnd::OnSetStatusPaneText(WPARAM wp, LPARAM lp)
{
	if(wp==0)
	{
		if(lp==0)
		{
			m_wndStatusBar.SetPaneText(STATUS_PANE_NUM, _T(""));
			m_wndStatusBar.SetPaneText(STATUS_PANE_SUM, _T(""));
		}
		else if(lp==STATUS_PANE_SUM)
			m_wndStatusBar.SetPaneText(STATUS_PANE_SUM, _T(""));
		else if(lp==STATUS_PANE_NUM)
			m_wndStatusBar.SetPaneText(STATUS_PANE_NUM, _T(""));
	}
	else if(wp==STATUS_PANE_SUM)
	{
		CString fmt;
		if(!fmt.LoadString(IDS_STATUS_PANE_SUM))
			fmt=_T("Sum: %.2f T");

		CString str;
		str.Format(fmt, *(double*)lp);
		m_wndStatusBar.SetPaneText(wp, str);
	}
	else if(wp==STATUS_PANE_NUM)
	{
		CString fmt;
		if(!fmt.LoadString(IDS_STATUS_PANE_NUM))
			fmt=_T("Num: %u");

		CString str;
		str.Format(fmt, lp);
		m_wndStatusBar.SetPaneText(wp, str);
	}

	return 0;
}
