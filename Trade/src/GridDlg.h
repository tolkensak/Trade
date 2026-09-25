
#pragma once

#include "TableDlg.h"
#include "Column.h"


class GridDlg : public TableDlg
{
protected:
	class Data : public SmartObject
	{
	public:
		Data();
		virtual ~Data();

		OBJID oidUser;
		StringA straMoment;
	};
	typedef SmartPointer<Data> DataPtr;
	typedef CArray<DataPtr> DataPtrArray;

protected:
	GridDlg(UINT uIDTemplate, CWnd* pParent=NULL);

public:
	virtual ~GridDlg();

	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedBtnApply();

protected:
	ColumnArray m_arrColumn;
	DataPtrArray m_arrData;

	StringA m_straReload;
	StringA m_straFormatApply;

	BOOL LayColumn();
	void Reload();
	int Apply(UINT uMsgBtns);

	void GetApplyStr(StringA& stra);

	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
};
