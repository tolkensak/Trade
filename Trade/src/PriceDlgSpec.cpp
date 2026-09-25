
#include "stdafx.h"
#include "App.h"
#include "PriceDlgSpec.h"


BEGIN_MESSAGE_MAP(PriceDlgSpec, PriceDlg)
END_MESSAGE_MAP()


PriceDlgSpec::PriceDlgSpec(OBJID oidWare, CWnd* pParent /*=NULL*/)
	: PriceDlg(oidWare, pParent)
{
}

PriceDlgSpec::~PriceDlgSpec()
{
}

BOOL PriceDlgSpec::OnInitDialog()
{
	PriceDlg::OnInitDialog();

	Reload();

	return TRUE;
}
