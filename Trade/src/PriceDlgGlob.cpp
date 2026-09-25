
#include "stdafx.h"
#include "App.h"
#include "PriceDlgGlob.h"
#include "WareDlgNew.h"


BEGIN_MESSAGE_MAP(PriceDlgGlob, PriceDlg)
	ON_MESSAGE(UM_WARE_CHOOSED, &DealDlg::OnWareChoosed)
END_MESSAGE_MAP()


PriceDlgGlob::PriceDlgGlob(CWnd* pParent /*=NULL*/)
	: PriceDlg(0, pParent)
{
}

PriceDlgGlob::~PriceDlgGlob()
{
}

BOOL PriceDlgGlob::OnInitDialog()
{
	PriceDlg::OnInitDialog();

	m_edtWare.SubclassDlgItem(IDC_EDT_WARE, this);

	return TRUE;
}

LRESULT PriceDlgGlob::OnWareChoosed(WPARAM wp, LPARAM lp)
{
	m_oid=(OBJID)wp;
	Reload();

	return 0;
}
