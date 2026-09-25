
#pragma once

#include "ManipDlg.h"


class PriceDlg : public ManipDlg
{
protected:
	class Data : public SmartObject
	{
	public:
		Data(OBJID oid);
		virtual ~Data();

		OBJID oid;
		double dSpend;
		double dAppend;
		BOOL bPercent;
	};

	friend BOOL operator==(const PriceDlg::Data& data1, const PriceDlg::Data& data2);

protected:
	PriceDlg(OBJID oidWare, CWnd* pParent=NULL);

public:
	virtual ~PriceDlg();

	enum { IDD=IDD_PRICE };

protected:
	SmartPointer<Data> m_pDataOrg;

	OBJID m_oidUnitCat;

	void Reload();
	void ReloadCmbUnit();
	BOOL PrepareData(Data& data);

	virtual OBJID GetDesiredPermitID();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
};

inline OBJID PriceDlg::GetDesiredPermitID()
{ return ID_PERMIT_PRICE; }
