
#include "stdafx.h"
#include "App.h"
#include "UserView.h"
#include "UserDlgNew.h"
#include "UserDlgEdit.h"
#include "PasswordDlgSpec.h"
#include "EasyPermitDlgSpec.h"


IMPLEMENT_DYNCREATE(UserView, ContactView)

BEGIN_MESSAGE_MAP(UserView, ContactView)
	ON_COMMAND(ID_DATA_PERMIT, &UserView::OnDataPermit)
	ON_COMMAND(ID_DATA_PASSWORD, &UserView::OnDataPassword)
	ON_UPDATE_COMMAND_UI(ID_DATA_PERMIT, &UserView::OnUpdateDataPermit)
	ON_UPDATE_COMMAND_UI(ID_DATA_PASSWORD, &UserView::OnUpdateDataPassword)
END_MESSAGE_MAP()


UserView::UserView()
	: ContactView(IDR_USER, "`user`")
{
	m_rm.SetObject(ReloadMgr::objUser);
	m_straReload="call sp_user_list(null)";
	m_straReloadRow="call sp_user_list(%u)";

	int i=0;
	m_arrColumn.Add(Column(IDS_COL_LOGIN, Column::typeText, 100, i++));
	m_arrColumn.Add(Column(IDS_COL_DISABLED, Column::typeBoolean, 70, i++));
}

UserView::~UserView()
{
}

BOOL UserView::ContextMenu(HMENU hMenu, UINT* puFlags, int iItem)
{
	if(!ContactView::ContextMenu(hMenu, puFlags, iItem))
		return FALSE;

	HMENU hMenuMain=AfxGetMainWnd()->GetMenu()->GetSafeHmenu();
	if(hMenuMain)
	{
		AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
		Menu_CopyItem(hMenu, -1, hMenuMain, ID_DATA_PASSWORD, TRUE);
		Menu_CopyItem(hMenu, -1, hMenuMain, ID_DATA_PERMIT, TRUE);
	}

	return TRUE;
}

BOOL UserView::DataNew(OBJID& oid)
{
	UserDlgNew dlg;
	if(dlg.DoModal()==IDOK)
	{
		oid=dlg.GetObjID();
		return TRUE;
	}

	return FALSE;
}

BOOL UserView::DataEdit(OBJID& oid)
{
	UserDlgEdit dlg(oid);
	if(dlg.DoModal()==IDOK)
	{
		oid=dlg.GetObjID();
		return TRUE;
	}

	return FALSE;
}

void UserView::OnDataPermit()
{
	OBJID oid=GetFirstSelectedItemObjID();
	if(oid)
	{
		EasyPermitDlgSpec dlg(oid);
		if(dlg.DoModal()==IDOK)
			Reload(dlg.GetObjID());
	}
}

void UserView::OnDataPassword()
{
	OBJID oid=GetFirstSelectedItemObjID();
	if(oid)
	{
		PasswordDlgSpec dlg(oid);
		dlg.DoModal();
	}
}

void UserView::OnUpdateDataPermit(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetListCtrl().GetSelectedCount()==1);
}

void UserView::OnUpdateDataPassword(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetListCtrl().GetSelectedCount()==1);
}
