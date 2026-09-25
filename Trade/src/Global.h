
#pragma once


#define UM_VIEW_ACTIVATED       (WM_USER+1) // wp: 0; lp: 0 or lot_id for SellView
#define UM_SET_STATUS_PANE_TEXT (WM_USER+2)
#define UM_WARE_CHOOSED         (WM_USER+3) // wp: ware id


#define STATUS_PANE_SUM  1
#define STATUS_PANE_NUM  2


#ifndef OBJID_DEFINED
#define OBJID_DEFINED
typedef UINT OBJID;
typedef OBJID *POBJID;
#endif


inline int Utf8ToWchar(LPCSTR pcSrc, int lenSrc, LPWSTR pcDest, int lenDest=TOL_MAXSTR)
{ return MultiByteToWideChar(CP_UTF8, 0, pcSrc, lenSrc+1, pcDest, lenDest); }

#define WcharToUtf8(cstr) \
((PCCharA)StringA((PCChar)(cstr), (cstr).GetLength(), CP_UTF8))

#define SetStatusPaneText(pane, text) \
((void)AfxGetMainWnd()->SendMessage(UM_SET_STATUS_PANE_TEXT, (WPARAM)(pane), (LPARAM)(text)))
