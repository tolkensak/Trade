
#pragma once


class User : public Object
{
public:
	User();
	virtual ~User();

	OBJID GetID() const;
	DWORD GetPermit() const;
	OBJID GetDesk() const;

	void SetDesk(OBJID oidDesk);
	void Save();

private:
	OBJID m_oid;
	DWORD m_dwPermit;
	OBJID m_oidDesk;

	void operator()(OBJID oid, DWORD dwPermit, OBJID oidDesk);

	friend class LoginDlg;
};


inline OBJID User::GetID() const
{ return m_oid; }

inline DWORD User::GetPermit() const
{ return m_dwPermit; }

inline OBJID User::GetDesk() const
{ return m_oidDesk; }
