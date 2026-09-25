
#include "stdafx.h"
#include "App.h"
#include "IndentDlgEdit.h"


BEGIN_MESSAGE_MAP(IndentDlgEdit, IndentDlg)
END_MESSAGE_MAP()


IndentDlgEdit::IndentDlgEdit(OBJID oidLot, CWnd* pParent /*=NULL*/)
	: IndentDlg(oidLot, pParent)
{
	m_uTitleFormatID=IDS_TITLE_EDIT;
}

IndentDlgEdit::~IndentDlgEdit()
{
}

void IndentDlgEdit::ReloadCmbClient()
{
	CbReload(IDC_CMB_CLIENT, "select id, name from client order by name", -1, m_oidClient);
}

BOOL IndentDlgEdit::OnInitDialog()
{
	IndentDlg::OnInitDialog();

	StringA stra;
	stra.Format("call sp_indent_edit(%u)", m_oid);

	MySQLResPtr pRes=theApp.Query(stra, this);
	if(!pRes)
		return TRUE;

	MYSQL_ROW row=pRes->FetchRow();
	if(!row)
		return TRUE;

	int i=0;
	m_oidClient=atoi(row[i]);

	i++;
	COleDateTime date;
	String str(row[i], -1, CP_UTF8);
	date.ParseDateTime(str);
	((CDateTimeCtrl*)GetDlgItem(IDC_DATE_DELIVER))->SetTime(date);

	ReloadCmbClient();

	return TRUE;
}

void IndentDlgEdit::OnOK()
{
	if(!PrepareData())
		return;

	StringA stra;
	stra.Format("update indent set cid=%u, deliver='%S' where lid=%u", m_oidClient, m_strDeliver, m_oid);

	if(!theApp.Exec(stra, this))
		return;

	m_rm.SetModified(ReloadMgr::oprEdit);

	IndentDlg::OnOK();
}
