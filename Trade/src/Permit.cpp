
#include "stdafx.h"
#include "App.h"
#include "Permit.h"


Permit::Item::Item()
	: m_oid(0)
	, m_dwFlag(0)
{
}

Permit::Item::Item(OBJID oid, DWORD dwFlag)
	: m_oid(oid)
	, m_dwFlag(dwFlag)
{
}

Permit::Item::~Item()
{
}


Permit::Permit()
{
}

Permit::~Permit()
{
}

DWORD Permit::GetFlag(OBJID oid) const
{
	for(int i=m_arr.GetCount()-1; i>=0; i--)
		if(m_arr[i].GetID()==oid)
			return m_arr[i].GetFlag();

	return 0;
}

void Permit::Reload()
{
	m_arr.RemoveAll();

	StringA stra;
	stra="call sp_permit_list()";

	MySQLResPtr pRes=theApp.Query(stra);
	if(!pRes)
		return;

	m_arr.SetSize((int)pRes->NumRows());

	int i=0;
	MYSQL_ROW row;
	while(row=pRes->FetchRow())
		m_arr.SetAt(i++, Item(ID_PERMIT+atoi(row[0]), atol(row[1])));
}
