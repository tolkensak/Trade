
#include "stdafx.h"
#include "App.h"
#include "ReportParam.h"
#include "Misc.h"
#include "FormatStr.h"


DWORD ReportParam::m_dwCommonStyle=WS_CHILD|WS_DISABLED;
SIZE ReportParam::m_szSpace={0, 0};
int ReportParam::m_nHeight=0;


ReportParam::ReportParam()
	: m_uType(0)
	, m_uStyle(0)
	, m_hwndLabel(NULL)
	, m_hwnd(NULL)
	, m_hwnd2(NULL)
{
	m_szLabel.cx=0;
	m_szLabel.cy=0;
}

ReportParam::~ReportParam()
{
}

void ReportParam::Init(CDialog* pDlg)
{
	if(!pDlg)
		return;

	CRect rc(0, 0, 1000, 1000);
	pDlg->MapDialogRect(&rc);

	double dx=rc.Width()/(double)1000;
	double dy=rc.Height()/(double)1000;

	m_szSpace.cx=(int)(6*dx);
	m_szSpace.cy=(int)(6*dy);

	CComboBox wnd;
	rc.SetRectEmpty();
	if(wnd.Create(m_dwCommonStyle|CBS_DROPDOWNLIST, rc, pDlg, -1))
	{
		wnd.SetFont(pDlg->GetFont(), FALSE);
		wnd.GetWindowRect(&rc);
		m_nHeight=rc.Height();
	}
	else
		m_nHeight=(int)(12*dy);
}

UINT ReportParam::Create(UINT uType, UINT uStyle, LPCTSTR pcLabel, LPCSTR pcSource, LPCSTR pcDefault, CWnd* pParent, UINT uID)
{
	UINT uOldID=uID;

	if(uType==typeUnknown || pcLabel==NULL || pParent==NULL)
		return uOldID;

	m_uType=uType;
	m_uStyle=uStyle;

	CRect rc(0, 0, 100, GetHeight());

	if(m_uType!=typeBoolean || IsStyle(styleList))
	{
		CStatic label;
		if(!label.Create(pcLabel, m_dwCommonStyle/*|SS_RIGHT*/, rc, pParent, ++uID))
			return uOldID;

		label.SetFont(pParent->GetFont(), FALSE);

		m_hwndLabel=label.UnsubclassWindow();
		if(m_hwndLabel)
		{
			HDC hdc=GetDC(m_hwndLabel);
			GetTextExtentPoint32(hdc, pcLabel, lstrlen(pcLabel), &m_szLabel);
			ReleaseDC(m_hwndLabel, hdc);
		}
	}

	if(m_uType==typeText)
	{
		CEdit wnd;
		if(!wnd.Create(m_dwCommonStyle|WS_TABSTOP|ES_AUTOHSCROLL, rc, pParent, ++uID))
			return uOldID;

		wnd.SetFont(pParent->GetFont(), FALSE);

		if(pcDefault)
			wnd.SetWindowTextW((LPCTSTR)String(pcDefault, -1, CP_UTF8));

		m_hwnd=wnd.UnsubclassWindow();
		return uID;
	}
	else if(m_uType==typeList)
	{
		CComboBox wnd;
		if(!wnd.Create(m_dwCommonStyle|WS_TABSTOP|(IsStyle(styleWritable)?(CBS_AUTOHSCROLL|CBS_DROPDOWN):(CBS_DROPDOWNLIST)), rc, pParent, ++uID))
			return uOldID;

		wnd.SetFont(pParent->GetFont(), FALSE);

		if(pcSource)
			Cb_Reload(&wnd, pcSource, -1, pcDefault?atoi(pcDefault):0, IsStyle(styleIncludeAll));

		m_hwnd=wnd.UnsubclassWindow();
		return uID;
	}
	else if(m_uType==typeDate)
	{
		CDateTimeCtrl wnd;
		if(!wnd.Create(m_dwCommonStyle|WS_TABSTOP|DTS_SHORTDATECENTURYFORMAT, rc, pParent, ++uID))
			return uOldID;

		wnd.SetFont(pParent->GetFont(), FALSE);

		FormatStr fmt(FormatStr::typeCtrl, FormatStr::partDate);
		wnd.SetFormat(fmt);

		if(pcDefault)
		{
			String str(pcDefault, -1, CP_UTF8);
			if(!str.IsEmpty())
			{
				COleDateTime date;
				if(date.ParseDateTime((LPCTSTR)str, VAR_DATEVALUEONLY))
					wnd.SetTime(date);
			}
		}

		m_hwnd=wnd.UnsubclassWindow();
		return uID;
	}
	else if(m_uType==typeTime)
	{
		CDateTimeCtrl wnd;
		if(!wnd.Create(m_dwCommonStyle|WS_TABSTOP|DTS_TIMEFORMAT|DTS_UPDOWN, rc, pParent, ++uID))
			return uOldID;

		wnd.SetFont(pParent->GetFont(), FALSE);

		FormatStr fmt(FormatStr::typeCtrl, FormatStr::partTime);
		wnd.SetFormat(fmt);

		if(pcDefault)
		{
			String str(pcDefault, -1, CP_UTF8);
			if(!str.IsEmpty())
			{
				COleDateTime time;
				if(time.ParseDateTime((LPCTSTR)str, VAR_TIMEVALUEONLY))
					wnd.SetTime(time);
			}
		}

		m_hwnd=wnd.UnsubclassWindow();
		return uID;
	}
	else if(m_uType==typeDateTime)
	{
		CDateTimeCtrl wnd;
		if(!wnd.Create(m_dwCommonStyle|WS_TABSTOP|DTS_SHORTDATECENTURYFORMAT, rc, pParent, ++uID))
			return uOldID;

		CDateTimeCtrl wnd2;
		if(!wnd2.Create(m_dwCommonStyle|WS_TABSTOP|DTS_TIMEFORMAT|DTS_UPDOWN, rc, pParent, ++uID))
			return uOldID;

		wnd.SetFont(pParent->GetFont(), FALSE);
		wnd2.SetFont(pParent->GetFont(), FALSE);

		FormatStr fmtD(FormatStr::typeCtrl, FormatStr::partDate);
		wnd.SetFormat(fmtD);

		FormatStr fmtT(FormatStr::typeCtrl, FormatStr::partTime);
		wnd2.SetFormat(fmtT);

		TCHAR pch[255];
		if(pcDefault && MultiByteToWideChar(CP_UTF8, 0, pcDefault, -1, pch, 255))
		{
			COleDateTime dtm;

			if(_tcschr(pch, _T(';')))
			{
				LPTSTR pcNextPart=NULL;
				LPTSTR pcPart=_tcstok_s(pch, _T(";"), &pcNextPart);
				if(pcPart==pch)
				{
					if(dtm.ParseDateTime((LPCTSTR)pcPart, VAR_DATEVALUEONLY))
						wnd.SetTime(dtm);

					pcPart=_tcstok_s(NULL, _T(";"), &pcNextPart);
					if(pcPart && dtm.ParseDateTime((LPCTSTR)pcPart, VAR_TIMEVALUEONLY))
						wnd2.SetTime(dtm);
				}
				else if(dtm.ParseDateTime((LPCTSTR)pcPart, VAR_TIMEVALUEONLY))
					wnd2.SetTime(dtm);
			}
			else if(dtm.ParseDateTime((LPCTSTR)pch))
			{
				wnd.SetTime(dtm);
				wnd2.SetTime(dtm);
			}
		}

		m_hwnd=wnd.UnsubclassWindow();
		m_hwnd2=wnd2.UnsubclassWindow();
		return uID;
	}
	else if(m_uType==typeBoolean)
	{
		if(IsStyle(styleList))
		{
			CComboBox wnd;
			if(!wnd.Create(m_dwCommonStyle|WS_TABSTOP|CBS_DROPDOWNLIST, rc, pParent, ++uID))
				return uOldID;

			wnd.SetFont(pParent->GetFont(), FALSE);

			int nDefault=pcDefault?(atoi(pcDefault)?2:1):3;

			CString str;
			if(!str.LoadString(IDYES))
				str=_T("Yes");

			int nData=2;
			int i=wnd.AddString(str);
			if(i!=-1)
			{
				wnd.SetItemData(i, nData);
				if(nDefault==nData)
					wnd.SetCurSel(i);
			}

			if(!str.LoadString(IDNO))
				str=_T("No");

			nData=1;
			i=wnd.AddString(str);
			if(i!=-1)
			{
				wnd.SetItemData(i, nData);
				if(nDefault==nData)
					wnd.SetCurSel(i);
			}

			if(HasStyle(style3state))
			{
				str=_T("");

				nData=3;
				i=wnd.AddString(str);
				if(i!=-1)
				{
					wnd.SetItemData(i, nData);
					if(nDefault==nData)
						wnd.SetCurSel(i);
				}
			}

			m_hwnd=wnd.UnsubclassWindow();
			return uID;
		}
		else
		{
			CButton wnd;
			if(!wnd.Create(pcLabel, m_dwCommonStyle|WS_TABSTOP|(HasStyle(style3state)?BS_AUTO3STATE:BS_AUTOCHECKBOX), rc, pParent, ++uID))
				return uOldID;

			wnd.SetFont(pParent->GetFont(), FALSE);

			if(pcDefault)
				wnd.SetCheck(atoi(pcDefault)?BST_CHECKED:BST_UNCHECKED);
			else if(HasStyle(style3state))
				wnd.SetCheck(BST_INDETERMINATE);

			m_hwnd=wnd.UnsubclassWindow();
			return uID;
		}
	}

	return uOldID;
}

void ReportParam::Show(BOOL bShow) const
{
	int nShow=bShow?SW_SHOW:SW_HIDE;

	if(m_hwndLabel)
	{
		ShowWindow(m_hwndLabel, nShow);
		EnableWindow(m_hwndLabel, bShow);
	}

	ShowWindow(m_hwnd, nShow);
	EnableWindow(m_hwnd, bShow);

	if(m_hwnd2)
	{
		ShowWindow(m_hwnd2, nShow);
		EnableWindow(m_hwnd2, bShow);
	}
}

void ReportParam::Place(int nPos, LPCRECT prcForm, int nMaxLabelWidth) const
{
	if(!prcForm)
		return;

	int height=GetHeight();

	int x=prcForm->left;
	int y=prcForm->top+nPos*(height+GetSpaceY());

	if(m_hwndLabel)
	{
		MoveWindow(m_hwndLabel, x, y+(height-m_szLabel.cy)/2, m_szLabel.cx, m_szLabel.cy, FALSE);
		x+=nMaxLabelWidth;//+CTRL_SPACE_HORZ;
	}

	if(m_hwnd2)
	{
		int space=GetSpaceX();
		int cx=prcForm->right-x-space;
		int width=(int)(cx*.6);

		MoveWindow(m_hwnd, x, y, width, height, FALSE);
		x+=width+space;

		MoveWindow(m_hwnd2, x, y, cx-width, height, FALSE);
	}
	else
	{
		if(m_uType==typeList)
			height*=10;

		MoveWindow(m_hwnd, x, y, prcForm->right-x, height, FALSE);
	}
}

void ReportParam::SetFocus() const
{
	::SetFocus(m_hwnd);
}

HWND ReportParam::GetLastCtrl() const
{
	if(m_hwnd2)
		return m_hwnd2;

	return m_hwnd;
}

void ReportParam::SetPosition(HWND hWndInsertAfter) const
{
	if(!hWndInsertAfter)
		return;

	HWND hwnd=hWndInsertAfter;

	if(m_hwndLabel)
	{
		SetWindowPos(m_hwndLabel, hwnd, 0, 0, 0, 0, SWP_DEFERERASE|SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOMOVE|SWP_NOOWNERZORDER|SWP_NOREDRAW|SWP_NOSENDCHANGING|SWP_NOSIZE);
		hwnd=m_hwndLabel;
	}

	SetWindowPos(m_hwnd, hwnd, 0, 0, 0, 0, SWP_DEFERERASE|SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOMOVE|SWP_NOOWNERZORDER|SWP_NOREDRAW|SWP_NOSENDCHANGING|SWP_NOSIZE);
	hwnd=m_hwnd;

	if(m_hwnd2)
		SetWindowPos(m_hwnd2, hwnd, 0, 0, 0, 0, SWP_DEFERERASE|SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOMOVE|SWP_NOOWNERZORDER|SWP_NOREDRAW|SWP_NOSENDCHANGING|SWP_NOSIZE);
}

BOOL ReportParam::GetTextValue(StringA& straValue, BOOL bShowInfo)
{
	CString cstr;
	CWnd::FromHandle(m_hwnd)->GetWindowText(cstr);
	cstr.Empty();

	if(cstr.IsEmpty())
	{
		if(HasStyle(styleEmptyNull))
			straValue="null";
		else if(HasStyle(styleEmptyZero))
		{
			if(HasStyle(styleInteger|styleFloat))
				straValue="0";
			else
				straValue="''";
		}
		else if(bShowInfo)
		{
			ShowInfo(IDS_BAD_TEXT);
			return FALSE;
		}
	}
	else if(HasStyle(styleInteger|styleFloat))
		straValue.Copy(cstr, cstr.GetLength(), CP_UTF8);
	else
		straValue.Format("'%s'", WcharToUtf8(cstr));

	return TRUE;
}

BOOL ReportParam::GetValue(StringA& straValue, BOOL bShowInfo)
{
	if(m_uType==typeText)
		return GetTextValue(straValue, bShowInfo);
	else if(m_uType==typeList)
	{
		if(IsStyle(styleWritable))
			return GetTextValue(straValue, bShowInfo);
		else
		{
			OBJID oid=Cb_GetOid((CComboBox*)CWnd::FromHandle(m_hwnd));
			if(oid==0)
			{
				if(HasStyle(styleEmptyNull))
					straValue="null";
				else if(HasStyle(styleEmptyZero))
					straValue="0";
				else if(bShowInfo)
				{
					ShowInfo(IDS_BAD_SELECT);
					return FALSE;
				}
			}
			else if(oid==-1)
				straValue="null";
			else
				straValue.Format("%u", oid);
		}
	}
	else if(m_uType==typeDate)
	{
		COleDateTime val;
		((CDateTimeCtrl*)CWnd::FromHandle(m_hwnd))->GetTime(val);
		CString cstr=val.Format(FormatStr(FormatStr::typeStore, FormatStr::partDate));
		straValue.Format("'%s'", WcharToUtf8(cstr));
	}
	else if(m_uType==typeTime)
	{
		COleDateTime val;
		((CDateTimeCtrl*)CWnd::FromHandle(m_hwnd))->GetTime(val);
		CString cstr=val.Format(FormatStr(FormatStr::typeStore, FormatStr::partTime));
		straValue.Format("'%s'", WcharToUtf8(cstr));
	}
	else if(m_uType==typeDateTime)
	{
		COleDateTime val;
		((CDateTimeCtrl*)CWnd::FromHandle(m_hwnd))->GetTime(val);

		COleDateTime val2;
		((CDateTimeCtrl*)CWnd::FromHandle(m_hwnd2))->GetTime(val2);

		val.SetDateTime(val.GetYear(), val.GetMonth(), val.GetDay(), val2.GetHour(), val2.GetMinute(), val2.GetSecond());
		CString cstr=val.Format(FormatStr(FormatStr::typeStore, FormatStr::partDateTime));
		straValue.Format("'%s'", WcharToUtf8(cstr));
	}
	else if(m_uType==typeBoolean)
	{
		if(IsStyle(styleList))
		{
			OBJID oid=Cb_GetOid((CComboBox*)CWnd::FromHandle(m_hwnd));
			if(oid==0)
			{
				if(HasStyle(styleEmptyNull))
					straValue="null";
				else if(HasStyle(styleEmptyZero))
					straValue="0";
				else if(bShowInfo)
				{
					ShowInfo(IDS_BAD_SELECT);
					return FALSE;
				}
			}
			else if(oid==3)
				straValue="null";
			else
				straValue.Format("%u", oid-1);
		}
		else
		{
			int nCheck=((CButton*)CWnd::FromHandle(m_hwnd))->GetCheck();

			if(HasStyle(style3state) && nCheck==BST_INDETERMINATE)
				straValue="null";
			else
				straValue.Format("%u", nCheck);
		}
	}

	return TRUE;
}

int ReportParam::ShowInfo(UINT uTextID, UINT uType)
{
	if(!m_hwndLabel)
		return 0;

	CString cstr;
	(CWnd::FromHandle(m_hwndLabel))->GetWindowText(cstr);
	cstr.Remove(_T('&'));

	int nRet=MsgBox(CWnd::FromHandle(GetParent(m_hwnd)), uType, uTextID, cstr);

	SetFocus();

	return nRet;
}
