
#pragma once


class ReloadMgr : public Object
{
public:
	enum Operation
	{
		oprUnknown
		, oprNew
		, oprEdit
		, oprDelete
	};

	enum Object
	{
		objUnknown
		, objUnitCat=1
		, objWareCat=2
		, objUser=4
		, objFirm=8
		, objClient=16
		, objUnit=32
		, objWare=64
		, objPrice=128
		, objBuy=256
		, objSell=512
		, objIndent=1024
		, objContact=2048
	};

public:
	ReloadMgr(Object obj=objUnknown);
	virtual ~ReloadMgr();

	void SetObject(Object obj);

	BOOL IsModified() const;
	void SetModified(Operation opr);
	void UnsetModified();

protected:
	Object m_obj;

	static DWORD m_dwObject;
};


inline BOOL ReloadMgr::IsModified() const
{ return m_dwObject&m_obj; }
