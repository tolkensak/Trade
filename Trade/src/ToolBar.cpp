
#include "stdafx.h"
#include "ToolBar.h"


struct CToolBarData
{
	WORD wVersion;
	WORD wWidth;
	WORD wHeight;
	WORD wItemCount;
	//WORD aItems[wItemCount]

	WORD* items()
	{ return (WORD*)(this+1); }
};


IMPLEMENT_DYNAMIC(ToolBar, CToolBar)

BEGIN_MESSAGE_MAP(ToolBar, CToolBar)
END_MESSAGE_MAP()


ToolBar::ToolBar(PUINT puImageCmd, int nImageCmdCount)
	: m_puImageCmd(puImageCmd)
	, m_nImageCmdCount(nImageCmdCount)
{
}

ToolBar::~ToolBar()
{
}

BOOL ToolBar::LoadToolBar(LPCTSTR lpszResourceName)
{
	//if(!CToolBar::LoadToolBar(lpszResourceName))
	//	return FALSE;

	ASSERT_VALID(this);
	ASSERT(lpszResourceName != NULL);

	// determine location of the bitmap in resource fork
	//HINSTANCE hInst=AfxFindResourceHandle(lpszResourceName, RT_TOOLBAR);
	HINSTANCE hInst=AfxGetInstanceHandle();
	HRSRC hRsrc=::FindResource(hInst, lpszResourceName, RT_TOOLBAR);
	if (hRsrc == NULL)
		return FALSE;

	HGLOBAL hGlobal=LoadResource(hInst, hRsrc);
	if (hGlobal == NULL)
		return FALSE;

	CToolBarData* pData=(CToolBarData*)LockResource(hGlobal);
	if (pData == NULL)
		return FALSE;
	ASSERT(pData->wVersion == 1);

	UINT* pItems=new UINT[pData->wItemCount];
	for (int i=0; i < pData->wItemCount; i++)
		pItems[i]=pData->items()[i];
	BOOL bResult=SetButtons(pItems, pData->wItemCount);
	delete[] pItems;

	if (bResult)
	{
		// set new sizes of the buttons
		CSize sizeImage(pData->wWidth, pData->wHeight);
		CSize sizeButton(pData->wWidth + 7, pData->wHeight + 7);
		SetSizes(sizeButton, sizeImage);

		//// load bitmap now that sizes are known by the toolbar control
		//bResult=LoadBitmap(lpszResourceName);
	}

	UnlockResource(hGlobal);
	FreeResource(hGlobal);

	if(bResult)
		ResetImageIndex();

	return bResult;
}

BOOL ToolBar::LoadToolBar(UINT nIDResource)
{
	return LoadToolBar(MAKEINTRESOURCE(nIDResource));
}

int ToolBar::FindImageIndex(UINT uCmdID)
{
	for(int i=0; i<m_nImageCmdCount; i++)
		if(m_puImageCmd[i]==uCmdID)
			return i;

	return -1;
}

void ToolBar::ResetImageIndex()
{
	if(!m_puImageCmd || !m_nImageCmdCount)
		return;

	TBBUTTON tbb;
	TBBUTTONINFO tbbi;
	CToolBarCtrl& tbc=GetToolBarCtrl();

	tbbi.cbSize=sizeof(tbbi);
	tbbi.dwMask=TBIF_IMAGE;

	for(int i=tbc.GetButtonCount()-1; i>=0; i--)
	{
		tbc.GetButton(i, &tbb);
		tbbi.iImage=FindImageIndex(tbb.idCommand);
		if(tbbi.iImage>=0)
			tbc.SetButtonInfo(tbb.idCommand, &tbbi);
	}
}
