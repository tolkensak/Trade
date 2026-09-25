
#pragma once

#include "ToolBar.h"


class MainWnd : public TSDIMVMainWndLang
{
	DECLARE_DYNCREATE(MainWnd)

protected:
	MainWnd();

public:
	virtual ~MainWnd();

	virtual void UpdateResource(TSDIMVDocTemplate* pNewTemplate);
	virtual void UpdateMenu(HMENU hMenu, UINT uResID);

	afx_msg void OnDesk(UINT uCmdID);
	afx_msg LRESULT OnSetStatusPaneText(WPARAM wp, LPARAM lp);

protected:
	static const int s_nImageListCount=3;
	CImageList m_iml[s_nImageListCount];

	CReBar m_wndRebar;
	ToolBar m_wndToolbar;
	CStatusBar m_wndStatusBar;

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	DECLARE_MESSAGE_MAP()
};
