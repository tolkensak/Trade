
#pragma once

#include "ManipDlg.h"


class ContactDlg : public ManipDlg
{
protected:
	class Data : public SmartObject
	{
	public:
		Data();
		virtual ~Data();

		ValidStr cstrFirstName;
		ValidStr cstrLastName;
		ValidStr cstrPhone;
		ValidStr cstrMobile;
		ValidStr cstrAddress;
		ValidStr cstrComment;

		//void PrepareForDB(Data& data) const;
	};

	friend BOOL operator==(const ContactDlg::Data& data1, const ContactDlg::Data& data2);

protected:
	ContactDlg(OBJID oidContact, CWnd* pParent=NULL);

public:
	virtual ~ContactDlg();

	enum { IDD=IDD_CONTACT };

protected:
	BOOL PrepareData(Data& data);

	virtual OBJID GetDesiredPermitID();

	DECLARE_MESSAGE_MAP()
};

inline OBJID ContactDlg::GetDesiredPermitID()
{ return ID_PERMIT_CONTACT; }
