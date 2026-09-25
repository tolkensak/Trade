
#pragma once

#include "TableDlg.h"
#include "ReloadMgr.h"


class ManipDlg : public TableDlg
{
protected:
	ManipDlg(UINT uIDTemplate, OBJID oid=0, CWnd* pParent=NULL);

public:
	virtual ~ManipDlg();

	OBJID GetObjID() const;

protected:
	OBJID m_oid;
	ReloadMgr m_rm;

	DECLARE_MESSAGE_MAP()
};

inline OBJID ManipDlg::GetObjID() const
{ return m_oid; }
