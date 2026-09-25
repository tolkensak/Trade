
#pragma once


BOOL GetReportDir(CString& str);
BOOL GetTempDir(CString& str);

BOOL Report_Create(OBJID oidReport, StringA& straQuery, CWnd* pWndOwner);

BOOL Invoice_Show(OBJID oidLot, CWnd* pWndOwner);
BOOL Invoice_Export(OBJID oidLot, CWnd* pWndOwner);

void DeleteTempFiles();

#ifdef REPORT_COPY_TO_TEMP
void CleanTempFiles();
#else
BOOL GetReportURL(CString& str);
#endif
