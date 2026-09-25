
#pragma once


class ValidStr : public CString
{
public:
	//ValidStr();

	BOOL IsNull() const;
	BOOL IsValidID();
	BOOL IsValidName();
	BOOL IsValidNumber();

	//void SetNull();

	//void GetDBStr(CString& str) const;

	ValidStr& operator=(LPCTSTR pc);

//protected:
//	static const CString null;
};

//inline BOOL ValidStr::IsNull() const
//{ return *this==null; }
//
//inline void ValidStr::SetNull()
//{ *this=null; }
