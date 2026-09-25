
#pragma once


class Permit : public Object
{
public:
	class Item
	{
	public:
		Item();
		Item(OBJID oid, DWORD dwFlag);
		virtual ~Item();

		OBJID GetID() const;
		DWORD GetFlag() const;

	private:
		OBJID m_oid;
		DWORD m_dwFlag;
	};

	typedef CArray<Item, const Item&> ItemArray;

public:
	Permit();
	virtual ~Permit();

	DWORD GetFlag(OBJID oid) const;
	const ItemArray& GetArray() const;

private:
	ItemArray m_arr;

	void Reload();
	friend class App;
};

inline const Permit::ItemArray& Permit::GetArray() const
{ return m_arr; }

inline OBJID Permit::Item::GetID() const
{ return m_oid; }

inline DWORD Permit::Item::GetFlag() const
{ return m_dwFlag; }
