
#include "stdafx.h"
#include "ValidStr.h"

//const CString ValidStr::null=_T("<NULL>");


//ValidStr::ValidStr()
//	: CString(null)
//{
//}

ValidStr& ValidStr::operator=(LPCTSTR pc)
{
	CString::operator=(pc);
	return *this;
}

//void ValidStr::GetDBStr(CString& str) const
//{
//	if(IsNull())
//		str=_T("NULL");
//	else
//		str.Format(_T("\'%s\'"), (LPCTSTR)*this);
//}

BOOL ValidStr::IsValidID()
{
	Trim();

	if(IsEmpty())
		return FALSE;

	for(int i=GetLength()-1; i>=0; i--)
		if(!_istdigit(GetAt(i)))
			return FALSE;

	return TRUE;
}

BOOL ValidStr::IsValidName()
{
	Trim();

	if(IsEmpty())
		return FALSE;

	//TCHAR ch;
	//for(int i=GetLength()-1; i>=0; i--)
	//{
	//	ch=GetAt(i);
	//	if(!_istalnum(ch)
	//		&& ch!=_T('.')
	//		&& ch!=_T(',')
	//		&& ch!=_T(' ')
	//		&& ch!=_T('_')
	//		&& ch!=_T('(')
	//		&& ch!=_T(')')
	//		&& ch!=_T('[')
	//		&& ch!=_T(']')
	//		&& ch!=_T('<')
	//		&& ch!=_T('>')
	//		)
	//		return FALSE;
	//}

	return TRUE;
}

BOOL ValidStr::IsValidNumber()
{
	Trim();

	if(IsEmpty())
		return FALSE;

	BOOL bDot=FALSE;
	TCHAR ch;

	for(int i=GetLength()-1; i>=0; i--)
	{
		ch=GetAt(i);

		if(!_istdigit(ch))
		{
			if(ch==_T('.'))
			{
				if(bDot)
					return FALSE;

				bDot=TRUE;
			}
			else
				return FALSE;
		}
	}

	if(bDot && GetLength()==1)
		return FALSE;

	return TRUE;
}
