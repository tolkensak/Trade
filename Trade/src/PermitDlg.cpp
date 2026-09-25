
#include "stdafx.h"
#include "App.h"
#include "PermitDlg.h"


BEGIN_MESSAGE_MAP(PermitDlg, ManipDlg)
END_MESSAGE_MAP()


PermitDlg::PermitDlg(UINT uIDTemplate, OBJID oidUser, CWnd* pParent /*=NULL*/)
	: ManipDlg(uIDTemplate, oidUser, pParent)
	, m_bCheckStateChangable(FALSE)
	, m_bSetted(FALSE)
	, m_dwPermit(0)
{
	m_uTitleFormatID=IDS_TITLE_CHANGE;
}

PermitDlg::~PermitDlg()
{
}

void PermitDlg::Reload()
{
	if(m_bSetted)  // permit may not be zero, becouse SetUserPermit.
	{
		m_bSetted=FALSE;
		CbSelect(IDC_CMB_USER, -1, m_oid);
	}
	else
	{
		StringA stra;
		stra.Format("call sp_permit_reload(%u)", m_oid);

		MySQLResPtr pRes=theApp.Query(stra, this);
		if(!pRes)
			return;

		MYSQL_ROW row=pRes->FetchRow();
		if(!row)
			return;

		m_dwPermit=atol(row[0]);
	}

	UpdateCheckState();
}

void PermitDlg::SetUser(const PermitDlg& dlg)
{
	SetUser(dlg.GetObjID(), dlg.GetPermit());
}

void PermitDlg::SetUser(OBJID oidUser, DWORD dwPermit)
{
	m_bSetted=TRUE;
	m_oid=oidUser;
	m_dwPermit=dwPermit;
}

BOOL PermitDlg::OnInitDialog()
{
	ManipDlg::OnInitDialog();

	CListCtrl* pList=(CListCtrl*)GetDlgItem(IDC_LIST);
	DWORD dwStyle=GetWindowLongPtr(pList->GetSafeHwnd(), GWL_STYLE);
	SetWindowLongPtr(pList->GetSafeHwnd(), GWL_STYLE, dwStyle|LVS_REPORT|LVS_SHOWSELALWAYS|LVS_NOCOLUMNHEADER);
	pList->SetExtendedStyle(LVS_EX_CHECKBOXES);

	RECT rc;
	pList->GetClientRect(&rc);
	rc.right-=GetSystemMetrics(SM_CXVSCROLL);
	pList->InsertColumn(0, NULL, 0, rc.right, 0);

	return TRUE;
}

void PermitDlg::OnOK()
{
	if(m_oid==1)
	{
		MsgBox(this, MB_ICONINFORMATION, IDS_ERR_TOUCH_ROOT);
		return;
	}

	if(m_oid==0)
	{
		ShowInfo(IDC_CMB_USER, IDS_BAD_SELECT);
		return;
	}

	StringA stra;
	stra.Format("update `user` set permit=%u where id=%u", m_dwPermit, m_oid);

	if(!theApp.Exec(stra, this))
		return;

	ManipDlg::OnOK();
}
