
#include "stdafx.h"
#include "App.h"
#include "Report.h"
#include <dlgs.h>


// globals

CStringArray _arrTempFilePath;
CMap<OBJID, OBJID, CString, CString&> _mapInvoiceFilePath;


BOOL GetTempFilePath(CString& cstrFilePath);
BOOL GetExportFilePath(CString& cstrFilePath, CWnd* pWndOwner);
BOOL WriteReport(OBJID oidReport, StringA& straQuery, CString& cstrFilePath, CWnd* pWndOwner);

#ifdef REPORT_COPY_TO_TEMP
void CopyRelatedFiles(OBJID oidReport);
#endif

BOOL ShowReport(LPCTSTR pcFilePath, CWnd* pWndOwner);
BOOL CreateInvoice(OBJID oidLot, CString& cstrFilePath, CWnd* pWndOwner);


//////////////////////////////////////////////////////////////////////////////////////////////////


BOOL GetReportDir(CString& str)
{
	static TCHAR pchDir[MAX_PATH]={0};

	if(pchDir[0]==_T('\0'))
	{
		CString cstr;
		DWORD dw=MAX_PATH*sizeof(TCHAR);
		if(Reg_GetValue(HKEY_LOCAL_MACHINE, _T("Software\\Tosare"), _T(""), NULL, (LPBYTE)cstr.GetBuffer(MAX_PATH), &dw)!=ERROR_SUCCESS)
			return FALSE;

		cstr.ReleaseBuffer();
		cstr.Trim();
		if(cstr.IsEmpty())
			return FALSE;

		if(!ExpandEnvironmentStrings(cstr, pchDir, MAX_PATH))
			return FALSE;

		PathAppend(pchDir, _T("Report"));

		////if(FAILED(SHGetFolderPath(NULL, CSIDL_COMMON_APPDATA, NULL, 0, pchDir)))
		//if(GetModuleFileName(AfxGetInstanceHandle(), pchDir, MAX_PATH)==0)
		//{
		//	pchDir[0]=_T('\0');
		//	MsgBox(NULL, MB_OK|MB_ICONERROR, _T("GetReportDir failed with error %d."), GetLastError());
		//	return FALSE;
		//}

		//PathRemoveFileSpec(pchDir);
		//PathAppend(pchDir, _T("Report"));
	}

	str=pchDir;
	return TRUE;
}

#ifndef REPORT_COPY_TO_TEMP
BOOL GetReportURL(CString& str)
{
	if(!GetReportDir(str))
		return FALSE;

	str.Replace(_T('\\'), _T('/'));
	str.Insert(0, _T("file:///"));
	return TRUE;
}
#endif

BOOL GetTempDir(CString& str)
{
	static TCHAR pchDir[MAX_PATH]={0};

	if(pchDir[0]==_T('\0'))
	{
		DWORD dwPathLen=GetTempPath(MAX_PATH, pchDir);
		if(dwPathLen>MAX_PATH)
		{
			pchDir[0]=_T('\0');
			MsgBox(NULL, MB_OK|MB_ICONERROR, _T("GetTempDir failed because buffer too small to hold the path."));
			return FALSE;
		}
		else if(dwPathLen==0)
		{
			pchDir[0]=_T('\0');
			MsgBox(NULL, MB_OK|MB_ICONERROR, _T("GetTempDir failed with error %d."), GetLastError());
			return FALSE;
		}

#ifdef REPORT_COPY_TO_TEMP
		Char pch[MAX_PATH];
		Char pchPath[MAX_PATH];
		Char pchCompany[MAX_PATH];
		Char pchProduct[MAX_PATH];
		Char pchVersion[MAX_PATH];

		GetModuleFileName(AfxGetInstanceHandle(), pchPath, TOL_MAXPATH);

		if(Version_GetSectionData(pchPath, _T("CompanyName"), pchCompany)!=VERSION_SUCCESS)
			Str_Copy(pchCompany, _T("UnkComp"));

		if(Version_GetSectionData(pchPath, _T("ProductName"), pchProduct)!=VERSION_SUCCESS)
			Str_Copy(pchProduct, _T("UnkProd"));

		if(Version_GetSectionData(pchPath, _T("ProductVersion"), pchVersion)!=VERSION_SUCCESS)
			Str_Copy(pchVersion, _T("UnkVer"));

		Str_Format(pch, _T("%s\\%s\\%s"), pchCompany, pchProduct, pchVersion);
		PathAppend(pchDir, pch);
#else
		srand((unsigned)time(NULL));
#endif

		Folder_EnsureExists(pchDir);
	}

	str=pchDir;
	return TRUE;
}

double RangedRand(int nMin, int nMax) // [nMin, nMax)
{
	return (double)rand()/(RAND_MAX+1)*(nMax-nMin)+nMin;
}

BOOL GetTempFilePath(CString& cstrFilePath)
{
	CString cstrTempDir;
	if(!GetTempDir(cstrTempDir))
		return FALSE;

#ifdef REPORT_COPY_TO_TEMP
	for(int i=1; 1; i++)
	{
		cstrFilePath.Format(_T("%s\\~%03u.xml"), cstrTempDir, i);
		if(!PathFileExists(cstrFilePath))
			return TRUE;
	}
#else
	while(1)
	{
		cstrFilePath.Format(_T("%s\\%x.xml"), cstrTempDir, (int)RangedRand(0x1001, 0xffff));
		if(!PathFileExists(cstrFilePath))
			return TRUE;
	}
#endif

	return FALSE;
}

UINT_PTR CALLBACK OFNMyHookProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if(uMsg==WM_INITDIALOG)
	{
		HWND hParent=GetParent(hDlg);
		Wnd_MoveToCenter(hParent, AfxGetMainWnd()->GetSafeHwnd());

		CString str;

		if(str.LoadString(IDS_TITLE_OFN_TYPE))
			SendMessage(hParent, CDM_SETCONTROLTEXT, stc2, (LPARAM)(LPCTSTR)str); // label for type combo

		if(str.LoadString(IDS_TITLE_OFN_FOLDER))
			SendMessage(hParent, CDM_SETCONTROLTEXT, stc4, (LPARAM)(LPCTSTR)str); // label for drive, folder combo

		if(str.LoadString(IDS_TITLE_OFN_FILE))
			SendMessage(hParent, CDM_SETCONTROLTEXT, stc3, (LPARAM)(LPCTSTR)str); // label for file combo or edit

		if(str.LoadString(IDS_TITLE_OFN_CONTENT))
			SendMessage(hParent, CDM_SETCONTROLTEXT, stc1, (LPARAM)(LPCTSTR)str); // label for folder content list

		if(str.LoadString(IDOK))
			SendMessage(hParent, CDM_SETCONTROLTEXT, IDOK, (LPARAM)(LPCTSTR)str);

		if(str.LoadString(IDCANCEL))
			SendMessage(hParent, CDM_SETCONTROLTEXT, IDCANCEL, (LPARAM)(LPCTSTR)str);
	}

	return 0;
}

BOOL GetExportFilePath(CString& cstrFilePath, CWnd* pWndOwner)
{
	static int nFilterIndex=1;

	CString cstrTitle;
	if(!cstrTitle.LoadString(IDS_TITLE_EXPORT))
		cstrTitle=_T("Export");

	OPENFILENAME ofn={0};
	ofn.lStructSize=sizeof(ofn);
	ofn.hwndOwner=pWndOwner?pWndOwner->GetSafeHwnd():AfxGetMainWnd()->GetSafeHwnd();
	//ofn.hInstance=NULL;
	ofn.lpstrFilter=_T("HTML\0*.htm;*.html\0XML\0*.xml\0");
	//ofn.lpstrCustomFilter=NULL;
	//ofn.nMaxCustFilter=0;
	ofn.nFilterIndex=nFilterIndex;
	ofn.lpstrFile=cstrFilePath.GetBuffer(MAX_PATH);
	ofn.nMaxFile=MAX_PATH;
	//ofn.lpstrFileTitle=NULL;
	//ofn.nMaxFileTitle=0;
	//ofn.lpstrInitialDir=NULL;
	ofn.lpstrTitle=cstrTitle;
	ofn.Flags=OFN_DONTADDTORECENT|OFN_ENABLESIZING|OFN_EXPLORER|OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_ENABLEHOOK;
	//ofn.nFileOffset=0;
	//ofn.nFileExtension=0;
	ofn.lpstrDefExt=_T("htm");
//	ofn.lCustData=0;
	ofn.lpfnHook=OFNMyHookProc;
//	ofn.lpTemplateName=NULL;
//#if (_WIN32_WINNT>=0x0500)
//	ofn.pvReserved=NULL;
//	ofn.dwReserved=0;
//	ofn.FlagsEx=0; //OFN_EX_NOPLACESBAR
//#endif // (_WIN32_WINNT >= 0x0500)

	BOOL bRet=GetSaveFileName(&ofn);
	if(bRet)
		nFilterIndex=ofn.nFilterIndex;

	cstrFilePath.ReleaseBuffer();
	return bRet;
}

BOOL WriteReport(OBJID oidReport, StringA& straQuery, CString& cstrFilePath, CWnd* pWndOwner)
{
	CWaitCursor wc;

#ifdef RESULT_IS_STRING

	MySQLResPtr pRes=theApp.Query(straQuery, pWndOwner);
	if(!pRes)
		return FALSE;

	MYSQL_ROW row=pRes->FetchRow();
	if(!row)
		return FALSE;

	if(!GetTempFilePath(cstrFilePath))
		return FALSE;

	HANDLE hFile=CreateFile(cstrFilePath,
						GENERIC_READ | GENERIC_WRITE, // open r-w
						0, // do not share
						NULL, // default security
						CREATE_ALWAYS, // overwrite existing
						FILE_ATTRIBUTE_NORMAL, // normal file
						NULL); // no template

	if(hFile==INVALID_HANDLE_VALUE)
	{
		MsgBox(pWndOwner, MB_OK|MB_ICONINFORMATION, _T("CreateFile failed with error %d."), GetLastError());
		return FALSE;
	}

	DWORD dwBytesWritten;
	PULONG len=pRes->FetchLengths();
	BOOL bSuccess=WriteFile(hFile, row[0], len[0], &dwBytesWritten, NULL);
	if(!bSuccess)
	{
		MsgBox(pWndOwner, MB_OK|MB_ICONINFORMATION, _T("WriteFile failed with error %d."), GetLastError());
		return FALSE;
	}

	bSuccess=CloseHandle(hFile);
	if(!bSuccess)
	{
		MsgBox(pWndOwner, MB_OK|MB_ICONINFORMATION, _T("CloseHandle failed with error %d."), GetLastError());
		return FALSE;
	}

#else

	if(!GetTempFilePath(cstrFilePath))
		return FALSE;

	HANDLE hFile=CreateFile(cstrFilePath,
						GENERIC_READ | GENERIC_WRITE, // open r-w
						0, // do not share
						NULL, // default security
						CREATE_ALWAYS, // overwrite existing
						FILE_ATTRIBUTE_NORMAL, // normal file
						NULL); // no template

	if(hFile==INVALID_HANDLE_VALUE)
	{
		MsgBox(pWndOwner, MB_OK|MB_ICONINFORMATION, _T("CreateFile failed with error %d."), GetLastError());
		return FALSE;
	}

	MySQLResPtr pRes=theApp.Query(straQuery, pWndOwner, TRUE);
	if(!pRes)
	{
		CloseHandle(hFile);
		return FALSE;
	}

	PULONG len;
	MYSQL_ROW row;
	DWORD dwBytesWritten;

	while(row=pRes->FetchRow())
	{
		len=pRes->FetchLengths();
		WriteFile(hFile, row[0], len[0], &dwBytesWritten, NULL);
	}

	CloseHandle(hFile);

#endif

#ifdef REPORT_COPY_TO_TEMP
	CopyRelatedFiles(oidReport);
#endif

	return TRUE;
}

#ifdef REPORT_COPY_TO_TEMP
void CopyRelatedFiles(OBJID oidReport)
{
	CString str;
	if(!GetReportDir(str))
		return;

	PathAppend(str.GetBuffer(MAX_PATH), _T("relation.xml"));
	str.ReleaseBuffer();

	XmlDoc xml;
	if(!xml.Open(str))
		return;

	xml.GetDocPtr()->setProperty((bstr_t)"SelectionLanguage", (_variant_t)"XPath");
	str.Format(_T("report[@id='%u' or @id='common']/file"), oidReport);
	MSXML2::IXMLDOMNodeListPtr listPtr=xml.GetDocPtr()->documentElement->selectNodes((_bstr_t)str);

	int n=listPtr->length;
	if(n==0)
		return;

	CString cstrReportDir;
	if(!GetReportDir(cstrReportDir))
		return;

	CString cstrTempDir;
	if(!GetTempDir(cstrTempDir))
		return;

	LPCTSTR pc;
	TCHAR pchReport[MAX_PATH];
	TCHAR pchTemp[MAX_PATH];
	BOOL bFailIfExists=!KEY_ISPRESSED(VK_CONTROL);

	for(int i=0; i<n; i++)
	{
		pc=listPtr->item[i]->text;
		PathCombine(pchReport, cstrReportDir, pc);
		PathCombine(pchTemp, cstrTempDir, pc);
		CopyFile(pchReport, pchTemp, bFailIfExists);
	}
}
#endif

BOOL ShowReport(LPCTSTR pcFilePath, CWnd* pWndOwner)
{
	ShellExecute(NULL, _T("open"), pcFilePath, NULL, NULL, SW_SHOWDEFAULT);
	return TRUE;
}

BOOL CreateInvoice(OBJID oidLot, CString& cstrFilePath, CWnd* pWndOwner)
{
	if(oidLot==0)
		return FALSE;

	cstrFilePath=_mapInvoiceFilePath[oidLot];
	if(!cstrFilePath.IsEmpty())
	{
		int nRet=MsgBox(pWndOwner, MB_ICONQUESTION|MB_YESNOCANCEL, IDS_PROMPT_REUSE);

		if(nRet==IDCANCEL)
			return FALSE;

		if(nRet==IDYES)
			return TRUE;

		cstrFilePath.Empty();
		_mapInvoiceFilePath[oidLot]=cstrFilePath;
	}

	StringA stra;
	stra.Format("select count(*) from sell_lot where lid=%u", oidLot);

	MySQLResPtr pRes=theApp.Query(stra, pWndOwner);
	if(!pRes)
		return FALSE;

	MYSQL_ROW row=pRes->FetchRow();
	if(!row)
		return FALSE;

	if(atoi(row[0])==0)
	{
		MsgBox(pWndOwner, MB_ICONINFORMATION, IDS_ERR_EMPTY_INDENT);
		return FALSE;
	}

#ifdef REPORT_COPY_TO_TEMP
	stra.Format("call rp_invoice(%u, %u)", oidLot, theApp.GetLangID());
#else
	CString cstrReportURL;
	if(!GetReportURL(cstrReportURL))
		return FALSE;

	stra.Format("call rp_invoice(%u, %u, '%s')", oidLot, theApp.GetLangID(), WcharToUtf8(cstrReportURL));
#endif

	if(!WriteReport(0, stra, cstrFilePath, pWndOwner))
		return FALSE;

	_mapInvoiceFilePath[oidLot]=cstrFilePath;
	return TRUE;
}

BOOL Invoice_Show(OBJID oidLot, CWnd* pWndOwner)
{
	if(!oidLot)
		return FALSE;

	CString str;
	if(!CreateInvoice(oidLot, str, pWndOwner))
		return FALSE;

	return ShowReport(str, pWndOwner);
}

BOOL Report_Create(OBJID oidReport, StringA& straQuery, CWnd* pWndOwner)
{
	if(straQuery.IsEmpty())
		return FALSE;

	CString str;
	if(!WriteReport(oidReport, straQuery, str, pWndOwner))
		return FALSE;

	_arrTempFilePath.Add(str);

	return ShowReport(str, pWndOwner);
}

BOOL Invoice_Export(OBJID oidLot, CWnd* pWndOwner)
{
	if(!oidLot)
		return FALSE;

	CString strSrcPath;
	if(!CreateInvoice(oidLot, strSrcPath, pWndOwner))
		return FALSE;

	CString strTitle;
	if(!strTitle.LoadString(IDS_TITLE_INVOICE))
		strTitle=_T("Invoice %u");

	StringA stra;
	stra.Format("select id from indent where lid=%u", oidLot);

	MySQLResPtr pRes=theApp.Query(stra, pWndOwner);
	if(!pRes)
		return FALSE;

	MYSQL_ROW row=pRes->FetchRow();
	if(!row)
		return FALSE;

	CString strDestPath;
	strDestPath.Format(strTitle, atol(row[0]));
	if(!GetExportFilePath(strDestPath, pWndOwner))
		return FALSE;

	LPCTSTR pcExt=PathFindExtension(strDestPath);
	if(lstrcmp(pcExt, _T(".xml"))==0)
	{
		CopyFile(strSrcPath, strDestPath, FALSE);
		return TRUE;
	}
	else if(lstrcmp(pcExt, _T(".htm"))==0 || lstrcmp(pcExt, _T(".html"))==0)
	{
		XML_Transform(strSrcPath, NULL, strDestPath);
		return TRUE;
	}

	return FALSE;
}

void DeleteTempFiles()
{
	for(int i=_arrTempFilePath.GetCount()-1; i>=0; i--)
		if(DeleteFile(_arrTempFilePath[i]))
			_arrTempFilePath.RemoveAt(i);
}

#ifdef REPORT_COPY_TO_TEMP
void CleanTempFiles()
{
	CString strTempDir;
	if(!GetTempDir(strTempDir))
		return;

	COleDateTime today=COleDateTime::GetCurrentTime();
	today.SetDateTime(today.GetYear(), today.GetMonth(), today.GetDay(), 0, 0, 0);

	UINT uByte;
	DATE* pLastDay;
	if(theApp.GetProfileBinary(_T(""), _T("LastCleaned"), (LPBYTE*)&pLastDay, &uByte))
	{
		COleDateTime lastDay(*pLastDay);
		delete[] pLastDay;
		pLastDay=NULL;

		if(today<=lastDay)
			return;
	}

	TCHAR pch[MAX_PATH]={0};
	PathCombine(pch, strTempDir, _T("~*.xml"));

	SHFILEOPSTRUCT fs={0};
	fs.wFunc=FO_DELETE;
	fs.pFrom=pch;
	fs.fFlags=FOF_NOCONFIRMATION|FOF_NOERRORUI|FOF_SILENT;
	SHFileOperation(&fs);

	theApp.WriteProfileBinary(_T(""), _T("LastCleaned"), (LPBYTE)&today.m_dt, sizeof(DATE));
}
#endif