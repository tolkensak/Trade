
#include "stdafx.h"
#include "App.h"
#include "ManipDlg.h"


BEGIN_MESSAGE_MAP(ManipDlg, TableDlg)
END_MESSAGE_MAP()


ManipDlg::ManipDlg(UINT uIDTemplate, OBJID oid, CWnd* pParent /*=NULL*/)
	: TableDlg(uIDTemplate, pParent)
	, m_oid(oid)
{
}

ManipDlg::~ManipDlg()
{
}
