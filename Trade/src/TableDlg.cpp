
#include "stdafx.h"
#include "App.h"
#include "TableDlg.h"

#define USING_RUN_AS

#ifdef USING_RUN_AS
#include "RunAsDlg.h"
#endif


BEGIN_MESSAGE_MAP(TableDlg, Dialog)
	ON_WM_CREATE()
END_MESSAGE_MAP()


TableDlg::TableDlg(UINT uIDTemplate, CWnd* pParent /*=NULL*/)
	: Dialog(uIDTemplate, pParent)
{
}

TableDlg::~TableDlg()
{
}

//#ifdef USING_RUN_AS
//
//DWORD WINAPI RunAsProc(LPVOID lpParam)
//{
//	RunAsDlg dlg((OBJID)lpParam);
//	return dlg.DoModal();
//}
//
//#endif

int TableDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if(!theApp.CheckPermit(GetDesiredPermitID()))
	{
#ifdef USING_RUN_AS

		//HANDLE hThread=CreateThread(NULL, 0, RunAsProc, (LPVOID)GetDesiredPermitID(), 0, NULL);
		//MsgWaitForMultipleObjects(1, &hThread, TRUE, INFINITE, QS_ALLINPUT|QS_KEY|QS_MOUSE|QS_MOUSEBUTTON|QS_MOUSEMOVE);

		//DWORD dwExitCode;
		//GetExitCodeThread(hThread, &dwExitCode);
		//if(dwExitCode!=IDOK)
		//	return -1;

		RunAsDlg dlg(GetDesiredPermitID());
		if(dlg.DoModal()!=IDOK)
			return -1;

		Wnd_MoveToCenter(m_hWnd, AfxGetMainWnd()->GetSafeHwnd());
#else

		MsgBox(GetOwner(), MB_ICONINFORMATION, IDS_ERR_NO_PERMIT);
		return -1;

#endif
	}

	return Dialog::OnCreate(lpCreateStruct);
}
