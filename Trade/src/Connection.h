
#pragma once

#include "Global.h"


class Connection : public MySQLConn
{
public:
	Connection();
	virtual ~Connection();

	OBJID GetNewObjID() const;

	BOOL IsShowError() const;
	void SetShowError(BOOL bShow=TRUE) const;

	CString ErrorStr() const;
	void ErrorStr(CString& str) const;

	void ShowError(CWnd* pParent=NULL) const;

protected:
	BOOL m_bShowError;
};

inline OBJID Connection::GetNewObjID() const
{ return (OBJID)InsertId(); }

inline BOOL Connection::IsShowError() const
{ return m_bShowError; }
