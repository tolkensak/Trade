
#include "stdafx.h"
#include "ReloadMgr.h"


DWORD ReloadMgr::m_dwObject=0;


ReloadMgr::ReloadMgr(Object obj)
	: m_obj(obj)
{
}

ReloadMgr::~ReloadMgr()
{
}

void ReloadMgr::SetObject(Object obj)
{
	m_obj=obj;
	//m_dwObject&=~m_obj;
}

void ReloadMgr::UnsetModified()
{
	m_dwObject&=~m_obj;
}

void ReloadMgr::SetModified(Operation opr)
{
	if(opr!=oprDelete)
		m_dwObject|=m_obj;

	switch(m_obj)
	{
	case objUnitCat:
		if(opr==oprEdit)
			m_dwObject|=objSell|objBuy|objWare|objUnit;
		else if(opr==oprDelete)
			m_dwObject|=objUnit;
		break;

	case objWareCat:
		if(opr==oprEdit)
			m_dwObject|=objSell|objBuy|objWare;
		else if(opr==oprDelete)
			m_dwObject|=objWare;
		break;

	case objFirm:
		if(opr==oprEdit)
			m_dwObject|=objWare;
		else if(opr==oprDelete)
			m_dwObject|=objWare;
		break;

	case objClient:
		if(opr==oprEdit)
			m_dwObject|=objIndent;
		break;

	case objUnit:
		if(opr==oprEdit)
			m_dwObject|=objSell|objBuy;
		break;

	case objWare:
		if(opr==oprEdit)
			m_dwObject|=objSell|objBuy;
		break;

	case objPrice:
		m_dwObject|=objSell|objBuy|objWare;
		break;

	//case objUser: break;
	//case objBuy: break;
	//case objSell: break;
	//case objIndent: break;
	//case objContact: break;
	}
}
