
#pragma once


class Column
{
public:
	enum Type
	{
		  typeInteger
		, typeText
		, typeSymbol
		, typeFloat
		, typeMoney
		, typeBoolean
		, typeDateTime
		, typeDate
		, typeTime
	};

public:
	Column();
	Column(UINT uStrID, Type type=typeText, int nWidth=-1, int nSubItem=-1);

	UINT GetStrID() const;
	Type GetType() const;
	int GetWidth() const;
	void SetWidth(int nWidth);
	int GetSubItem() const;
	int GetFormat() const;

protected:
	UINT m_uStrID;
	Type m_type;
	int m_nWidth;
	int m_nSubItem;
};

typedef CArray<Column, Column&> ColumnArray;



inline UINT Column::GetStrID() const
{ return m_uStrID; }

inline Column::Type Column::GetType() const
{ return m_type; }

inline int Column::GetWidth() const
{ return m_nWidth; }

inline void Column::SetWidth(int nWidth)
{ m_nWidth=nWidth; }

inline int Column::GetSubItem() const
{ return m_nSubItem; }
