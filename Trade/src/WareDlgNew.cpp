
#include "stdafx.h"
#include "App.h"
#include "WareDlgNew.h"


BEGIN_MESSAGE_MAP(WareDlgNew, WareDlg)
END_MESSAGE_MAP()


WareDlgNew::WareDlgNew(CWnd* pParent /*=NULL*/)
	: WareDlg(0, pParent)
{
	m_uTitleFormatID=IDS_TITLE_NEW;
}

WareDlgNew::~WareDlgNew()
{
}

void WareDlgNew::ReloadCmbFirm()
{
	CbReload(IDC_CMB_FIRM, "select id, name from firm where disabled is false order by name", -1, m_oidFirm);
}

void WareDlgNew::OnOK()
{
	ValidStr cstrName;
	if(!IsValid(cstrName))
		return;

	StringA stra;
	stra.Format("insert into ware(name, wcid, ucid, fid) values('%s', %u, %u, %u)"
		, WcharToUtf8(cstrName)
		, m_oidWareCat
		, m_oidUnitCat
		, m_oidFirm);

	m_oid=theApp.Insert(stra, this);
	if(m_oid==0)
		return;

	m_rm.SetModified(ReloadMgr::oprNew);

	WareDlg::OnOK();
}
