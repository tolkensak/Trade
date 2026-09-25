
#include "stdafx.h"
#include "Global.h"
#include "Indent.h"


Indent::Indent()
	: m_bChanged(FALSE)
	, m_oidLot(-1)
{
}

Indent::~Indent()
{
}


Indent theIndent;


void Indent::operator()(BOOL bChanged, OBJID oidLot, const CString& strID)
{
	m_bChanged=bChanged;
	m_oidLot=oidLot;
	m_strID=strID;
}
