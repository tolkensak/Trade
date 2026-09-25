
#include "stdafx.h"
#include "Connection.h"


Connection::Connection()
	: m_bShowError(TRUE)
{
}

Connection::~Connection()
{
}

void Connection::SetShowError(BOOL bShow) const
{
	Connection* pConn=const_cast<Connection*>(this);
	pConn->m_bShowError=bShow;
}

CString Connection::ErrorStr() const
{
	CString str;
	ErrorStr(str);
	return str;
}

void Connection::ErrorStr(CString& str) const
{
	str.Format(_T("Error %d\n%s"), Errno(), (PCChar)String(Error()));
}

void Connection::ShowError(CWnd* pParent) const
{
	if(m_bShowError)
		MsgBox(pParent, MB_OK|MB_ICONINFORMATION, ErrorStr());
}
