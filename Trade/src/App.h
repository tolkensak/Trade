
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"	// main symbols
#include "Global.h"
#include "Misc.h"
#include "User.h"
#include "Permit.h"
#include "Connection.h"
#include "ValidStr.h"


class App : public TSDIMVWinAppLang
{
public:
	App();
	virtual ~App();

	const Connection& Connect() const;
	BOOL Exec(const StringA& stra, CWnd* pParent=NULL) const;
	MySQLResPtr Query(const StringA& stra, CWnd* pParent=NULL, BOOL bUseResult=FALSE) const;
	OBJID Insert(const StringA& stra, CWnd* pParent=NULL) const;
	//void NextResult(MySQLResPtr& pRes) const;

	User& GetUser();
	const User& GetUser() const;
	const Permit& GetPermit() const;

	BOOL CheckPermit(OBJID oidPermit) const;
	//BOOL CheckPermit(const CUIntArray& arrPermitID) const;

	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void AddLangMenu(HMENU hMenu);

	afx_msg void OnDataMyPassword();
	afx_msg void OnDataReport();
	afx_msg void OnDeleteTempFile();

protected:
	User m_user;
	Permit m_permit;
	Connection m_conn;

	void AddDocTemplate(UINT uResID, CRuntimeClass* pViewClass);
	void CreateDeskMenu(HMENU hMenuParent);

	DECLARE_MESSAGE_MAP()
};

inline User& App::GetUser()
{ return m_user; }

inline const User& App::GetUser() const
{ return m_user; }

inline const Permit& App::GetPermit() const
{ return m_permit; }



extern App theApp;



inline UINT GetDeskResID(UINT uCmdID)
{ return uCmdID-ID_DESK_FIRST+IDR_MAIN; }

inline UINT GetDeskCmdID(UINT uResID)
{ return uResID-IDR_MAIN+ID_DESK_FIRST; }
