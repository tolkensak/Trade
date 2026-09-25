
#include "stdafx.h"
#include "App.h"
#include "IndentDlgNew.h"


BEGIN_MESSAGE_MAP(IndentDlgNew, IndentDlg)
END_MESSAGE_MAP()


IndentDlgNew::IndentDlgNew(CWnd* pParent /*=NULL*/)
	: IndentDlg(0, pParent)
{
	m_uTitleFormatID=IDS_TITLE_NEW;
}

IndentDlgNew::~IndentDlgNew()
{
}

void IndentDlgNew::ReloadCmbClient()
{
	CbReload(IDC_CMB_CLIENT, "select id, name from client where disabled = 0 order by name", -1, m_oidClient);
}

void IndentDlgNew::OnOK()
{
	if(!PrepareData())
		return;

	StringA stra;
	stra.Format("insert into indent(cid, deliver, uid) values(%u, '%S', %u)", m_oidClient, m_strDeliver, theApp.GetUser().GetID());

	OBJID oidIndent=theApp.Insert(stra, this);
	if(oidIndent==0)
		return;

	stra.Format("select lid from indent where id=%u", oidIndent);

	MySQLResPtr pRes=theApp.Query(stra, this);
	if(!pRes)
		return;

	MYSQL_ROW row=pRes->FetchRow();
	if(!row)
		return;

	m_oid=atoi(row[0]);
	if(m_oid==0)
		return;

	m_rm.SetModified(ReloadMgr::oprNew);

	IndentDlg::OnOK();
}
