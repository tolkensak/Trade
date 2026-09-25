
#include "stdafx.h"
#include "App.h"
#include "User.h"


User::User()
	: m_oid(0)
	, m_dwPermit(0)
	, m_oidDesk(0)
{
}

User::~User()
{
}

void User::operator()(OBJID oid, DWORD dwPermit, OBJID oidDesk)
{
	m_oid=oid;
	m_dwPermit=dwPermit;
	m_oidDesk=oidDesk;
}

void User::SetDesk(OBJID oidDesk)
{
	if(oidDesk!=m_oidDesk)
		m_oidDesk=oidDesk;
}

void User::Save()
{
	StringA stra;
	stra.Format("update user_set set desk=%u where uid=%u", GetDesk(), GetID());
	theApp.Exec(stra);
}
