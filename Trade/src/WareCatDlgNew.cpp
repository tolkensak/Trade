
#include "stdafx.h"
#include "App.h"
#include "WareCatDlgNew.h"


BEGIN_MESSAGE_MAP(WareCatDlgNew, WareCatDlg)
END_MESSAGE_MAP()


WareCatDlgNew::WareCatDlgNew(CWnd* pParent /*=NULL*/)
	: WareCatDlg(0, pParent)
{
	m_uTitleFormatID=IDS_TITLE_NEW;
}

WareCatDlgNew::~WareCatDlgNew()
{
}

void WareCatDlgNew::OnOK()
{
	ValidStr cstrName;
	GetDlgItemText(IDC_EDT_NAME, cstrName);
	if(!cstrName.IsValidName())
	{
		ShowInfo(IDC_EDT_NAME, IDS_BAD_TEXT);
		return;
	}

	StringA stra;
	stra.Format("insert into ware_cat(name) values('%s')", WcharToUtf8(cstrName));

	m_oid=theApp.Insert(stra, this);
	if(m_oid==0)
		return;

	m_rm.SetModified(ReloadMgr::oprNew);

	WareCatDlg::OnOK();
}
