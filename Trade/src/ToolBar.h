
#pragma once


class ToolBar : public CToolBar
{
	DECLARE_DYNAMIC(ToolBar)

public:
	ToolBar(PUINT puImageCmd=NULL, int nImageCmdCount=0);
	virtual ~ToolBar();

	BOOL LoadToolBar(LPCTSTR lpszResourceName);
	BOOL LoadToolBar(UINT nIDResource);

protected:
	PUINT m_puImageCmd;
	int m_nImageCmdCount;

	void ResetImageIndex();
	int FindImageIndex(UINT uCmdID);

	DECLARE_MESSAGE_MAP()
};


