
#pragma once


class ReportParam : public SmartObject
{
public:
	enum Type { typeUnknown, typeText, typeList, typeDate, typeTime, typeDateTime, typeBoolean };
	enum Style {
			//, styleText=0
			//, styleSelect=0
			  styleWritable=1
			, styleIncludeAll=2
			//, styleCheck=0
			, styleList=1
			, style3state=2
			// common
			, styleInteger=1024
			, styleFloat=2048
			, styleEmptyNull=4096
			, styleEmptyZero=8192
	};

public:
	ReportParam();
	~ReportParam();

	UINT Create(UINT uType, UINT uStyle, LPCTSTR pcLabel, LPCSTR pcSource, LPCSTR pcDefault, CWnd* pParent, UINT uID);
	void Show(BOOL bShow=TRUE) const;
	void Place(int nPos, LPCRECT prcForm, int nMaxLabelWidth) const;

	BOOL IsStyle(UINT uStyle) const;
	BOOL HasStyle(UINT uStyle) const;

	void GetLabelSize(LPSIZE psz) const;
	BOOL GetValue(StringA& straValue, BOOL bShowInfo=TRUE);

	void SetFocus() const;
	void SetPosition(HWND hWndInsertAfter) const;
	HWND GetLastCtrl() const;

	static void Init(CDialog* pDlg);
	static int GetSpaceX();
	static int GetSpaceY();
	static int GetHeight();

protected:
	static DWORD m_dwCommonStyle;
	static SIZE m_szDlgUnit;
	static SIZE m_szSpace;
	static int m_nHeight;

	UINT m_uType;
	UINT m_uStyle;

	HWND m_hwndLabel;
	HWND m_hwnd;
	HWND m_hwnd2;

	SIZE m_szLabel;

	int ShowInfo(UINT uTextID, UINT uType=MB_OK|MB_ICONINFORMATION);
	BOOL GetTextValue(StringA& straValue, BOOL bShowInfo);
};

typedef SmartPointer<ReportParam> ReportParamPtr;
typedef CArray<ReportParamPtr, ReportParamPtr> ReportParamPtrArray;


inline BOOL ReportParam::IsStyle(UINT uStyle) const
{ return ((m_uStyle&uStyle)==uStyle); }

inline BOOL ReportParam::HasStyle(UINT uStyle) const
{ return (m_uStyle&uStyle); }

inline void ReportParam::GetLabelSize(LPSIZE psz) const
{ if(psz) { psz->cx=m_szLabel.cx; psz->cy=m_szLabel.cy; } }

inline int ReportParam::GetSpaceX()
{ return m_szSpace.cx; }

inline int ReportParam::GetSpaceY()
{ return m_szSpace.cy; }

inline int ReportParam::GetHeight()
{ return m_nHeight; }
