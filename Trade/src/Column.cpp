
#include "stdafx.h"
#include "Column.h"


Column::Column()
	: m_uStrID(0)
	, m_type(typeText)
	, m_nWidth(-1)
	, m_nSubItem(-1)
{
}

Column::Column(UINT uStrID, Type type, int nWidth, int nSubItem)
	: m_uStrID(uStrID)
	, m_type(type)
	, m_nWidth(nWidth)
	, m_nSubItem(nSubItem)
{
}

int Column::GetFormat() const
{
	switch(m_type)
	{
	case typeFloat:
	case typeMoney:
		return LVCFMT_RIGHT;
	case typeInteger:
	case typeSymbol:
	case typeBoolean:
		return LVCFMT_CENTER;
	}

	return LVCFMT_LEFT;
}

