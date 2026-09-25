
#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN	// Exclude rarely-used stuff from Windows headers
#endif


#include "targetver.h"


#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit
#define _AFX_ALL_WARNINGS	// turns off MFC's hiding of some common and often safely ignored warning messages


#include <afxwin.h>	// MFC core and standard components
#include <afxext.h>	// MFC extensions
#include <afxcview.h>

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>	// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <atlcomtime.h> // ATL::COleDateTime
#include <shlwapi.h> // path operations
#include <afxdtctl.h> // CDateTimeCtrl



#ifdef _DEBUG
//#define TOLCDLL
#define TOLPDLL
#define TOLMYSQLDLL
#define TOLMFCDLL
#define TOLXMLDLL
#endif

#include <tolc_menu.h>
#include <tolc_util.h>
#include <tolc_version.h>
#include <tolc_string.h>
#include <tolc_register.h>

#include <tolcpp_string.h>
#include <tolcpp_pointer.h>

#include <tolmysql_mysql.h>

#include <tolmfc_SDIMV_WinApp_Lang.h>
#include <tolmfc_SDIMV_MainWnd_Lang.h>
#include <tolmfc_util.h>

#include <tolxml_util.h>
#include <tolxml_doc.h>

TOLNS_USING
TOLNS_XML_USING
TOLNS_MYSQL_USING




#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


