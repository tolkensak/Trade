
#pragma once


#include "ReportParam.h"


class ReportForm : public SmartObject
{
public:
	ReportForm(OBJID oidForm);
	~ReportForm();

	OBJID GetID() const;
	int GetHeight() const;

	int Add(ReportParamPtr pParam, HWND hWndInsertAfter);
	void Show(BOOL bShow=TRUE) const;
	void Place(LPCRECT prcForm) const;

	void SetFocus(int nParam=0) const;
	BOOL GetValue(StringA& straValue, BOOL bShowInfo=TRUE);

protected:
	OBJID m_oidForm;
	CSize m_szMaxLabel;

	ReportParamPtrArray m_arrParamPtr;
};

inline OBJID ReportForm::GetID() const
{
	return m_oidForm;
}

typedef SmartPointer<ReportForm> ReportFormPtr;
typedef CMap<OBJID, OBJID, ReportFormPtr, ReportFormPtr> ReportFormPtrMap;
