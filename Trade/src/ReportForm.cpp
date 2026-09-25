
#include "stdafx.h"
#include "App.h"
#include "ReportForm.h"


ReportForm::ReportForm(OBJID oidForm)
	: m_oidForm(oidForm)
	, m_szMaxLabel(0, 0)
{
}

ReportForm::~ReportForm()
{
}

void ReportForm::Show(BOOL bShow) const
{
	int n=m_arrParamPtr.GetCount();
	for(int i=0; i<n; i++)
		m_arrParamPtr[i]->Show(bShow);
}

void ReportForm::SetFocus(int nParam) const
{
	if(nParam>=0 && nParam<m_arrParamPtr.GetCount())
		m_arrParamPtr[nParam]->SetFocus();
}

int ReportForm::Add(ReportParamPtr pParam, HWND hWndInsertAfter)
{
	if(pParam)
	{
		SIZE sz;
		pParam->GetLabelSize(&sz);

		if(sz.cx>m_szMaxLabel.cx)
			m_szMaxLabel.cx=sz.cx;

		if(sz.cy>m_szMaxLabel.cy)
			m_szMaxLabel.cy=sz.cy;

		int i=m_arrParamPtr.Add(pParam);
		pParam->SetPosition(i>0?m_arrParamPtr[i-1]->GetLastCtrl():hWndInsertAfter);
		return i;
	}

	return -1;
}

void ReportForm::Place(LPCRECT prcForm) const
{
	if(!prcForm)
		return;

	int n=m_arrParamPtr.GetCount();
	for(int i=0; i<n; i++)
		m_arrParamPtr[i]->Place(i, prcForm, m_szMaxLabel.cx);
}

int ReportForm::GetHeight() const
{
	int n=m_arrParamPtr.GetCount();
	if(n)
		return n*ReportParam::GetHeight()+(n-1)*ReportParam::GetSpaceY();

	return 0;
}

BOOL ReportForm::GetValue(StringA& straValue, BOOL bShowInfo)
{
	StringA stra;
	int n=m_arrParamPtr.GetCount();
	for(int i=0; i<n; i++)
	{
		if(!m_arrParamPtr[i]->GetValue(stra, bShowInfo))
			return FALSE;

		if(i)
			straValue+=",";

		straValue+=stra;
	}

	return TRUE;
}
