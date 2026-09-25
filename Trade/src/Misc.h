
#pragma once


double GetUnitRatio(OBJID oidUnit);

OBJID Cb_GetOid(CComboBox* pCb, int nItem=-1);
void Cb_Select(CComboBox* pCb, int nSelect=-1, OBJID oidSelect=FALSE);
void Cb_Reload(CComboBox* pCb, const StringA& straQuery, int nSelect=-1, OBJID oidSelect=FALSE, BOOL bIncludeAll=FALSE);
