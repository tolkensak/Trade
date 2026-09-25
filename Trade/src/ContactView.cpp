
#include "stdafx.h"
#include "App.h"
#include "ContactView.h"
#include "ContactDlgSpec.h"


BEGIN_MESSAGE_MAP(ContactView, TableView)
	ON_COMMAND(ID_DATA_CONTACT, &ContactView::OnDataContact)
	ON_UPDATE_COMMAND_UI(ID_DATA_CONTACT, &ContactView::OnUpdateDataContact)
END_MESSAGE_MAP()


ContactView::ContactView(UINT uUniqueID, PCCharA pcTable)
	: TableView(uUniqueID)
	, m_straTable(pcTable)
{
}

ContactView::~ContactView()
{
}

BOOL ContactView::ContextMenu(HMENU hMenu, UINT* puFlags, int iItem)
{
	if(!TableView::ContextMenu(hMenu, puFlags, iItem))
		return FALSE;

	HMENU hMenuMain=AfxGetMainWnd()->GetMenu()->GetSafeHmenu();
	if(hMenuMain)
	{
		AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
		Menu_CopyItem(hMenu, -1, hMenuMain, ID_DATA_CONTACT, TRUE);
	}

	return TRUE;
}

void ContactView::OnDataContact()
{
	OBJID oid=GetFirstSelectedItemObjID();
	if(oid==0)
		return;

	StringA stra;
	stra.Format("select coid from %s where id=%u", (PCCharA)m_straTable, oid);

	MySQLResPtr pRes=theApp.Query(stra, this);
	if(!pRes)
		return;

	MYSQL_ROW row=pRes->FetchRow();
	if(!row)
		return;

	ContactDlgSpec dlg(atoi(row[0]));
	dlg.DoModal();
}

void ContactView::OnUpdateDataContact(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetListCtrl().GetSelectedCount()==1);
}
