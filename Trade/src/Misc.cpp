
#include "stdafx.h"
#include "App.h"
#include "Misc.h"


double GetUnitRatio(OBJID oidUnit)
{
	StringA stra;
	stra.Format("call sp_unit_ratio(%u)", oidUnit);

	MySQLResPtr pRes=theApp.Query(stra);
	if(!pRes)
		return 0;

	MYSQL_ROW row=pRes->FetchRow();
	if(!row)
		return 0;

	return atof(row[0]);
}

OBJID Cb_GetOid(CComboBox* pCb, int nItem)
{
	if(!pCb)
		return 0;

	if(nItem==-1)
		nItem=pCb->GetCurSel();

	if(nItem!=-1)
		return (OBJID)pCb->GetItemData(nItem);

	return 0;
}

void Cb_Select(CComboBox* pCb, int nSelect, OBJID oidSelect)
{
	if(!pCb)
		return;

	if(nSelect==-1 && oidSelect==0)
		return;

	OBJID oid;
	int n=pCb->GetCount();

	for(int i=0; i<n; i++)
	{
		if(nSelect==-1)
		{
			oid=(OBJID)pCb->GetItemData(i);
			if(oid==oidSelect)
			{
				pCb->SetCurSel(i);
				return;
			}
		}
		else if(i==nSelect)
		{
			pCb->SetCurSel(i);
			return;
		}
	}
}

void Cb_Reload(CComboBox* pCb, const StringA& straQuery, int nSelect, OBJID oidSelect, BOOL bIncludeAll)
{
	if(!pCb)
		return;

	pCb->ResetContent();

	if(straQuery.IsEmpty())
		return;

	MySQLResPtr pRes=theApp.Query(straQuery, pCb->GetParent());
	if(!pRes)
		return;

	int i;
	OBJID oid;

	if(bIncludeAll)
	{
		CString str;
		if(str.LoadString(IDS_COMBOBOX_ALL))
		{
			i=pCb->AddString(str);
			if(i!=-1)
			{
				oid=-1;
				pCb->SetItemData(i, oid);

				if(nSelect!=-1)
				{
					if(i==nSelect)
					{
						pCb->SetCurSel(i);
						nSelect=-1;
						oidSelect=0;
					}
				}
				else if(oidSelect!=0)
				{
					if(oid==oidSelect)
					{
						pCb->SetCurSel(i);
						nSelect=-1;
						oidSelect=0;
					}
				}
			}
		}
	}

	PULONG len;
	MYSQL_ROW row;
	static TCHAR pch[TOL_MAXSTR];

	while(row=pRes->FetchRow())
	{
		len=pRes->FetchLengths();
		Utf8ToWchar(row[1], len[1], pch);

		i=pCb->AddString(pch);
		if(i==-1)
			continue;

		oid=atoi(row[0]);
		pCb->SetItemData(i, oid);

		if(nSelect!=-1)
		{
			if(i==nSelect)
			{
				pCb->SetCurSel(i);
				nSelect=-1;
				oidSelect=0;
			}
		}
		else if(oidSelect!=0)
		{
			if(oid==oidSelect)
			{
				pCb->SetCurSel(i);
				nSelect=-1;
				oidSelect=0;
			}
		}
	}
}
