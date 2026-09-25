
#pragma once


class MainView : public CView
{
	DECLARE_DYNCREATE(MainView)

protected:
	MainView();           // protected constructor used by dynamic creation
	virtual ~MainView();

public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view

protected:
	DECLARE_MESSAGE_MAP()
};
