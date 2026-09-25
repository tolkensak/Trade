
#pragma once


class Indent : public Object
{
public:
	Indent();
	virtual ~Indent();

	BOOL IsChanged() const;

	OBJID GetLotID() const;
	const CString& GetID() const;

protected:
	BOOL m_bChanged;
	OBJID m_oidLot;
	CString m_strID;

	void ApplyChange();
	void operator()(BOOL bChanged=TRUE, OBJID oidLot=-1, const CString& strID=_T(""));

	friend class SellView;
	friend class IndentView;
};


inline BOOL Indent::IsChanged() const
{ return m_bChanged; }

inline OBJID Indent::GetLotID() const
{ return m_oidLot; }

inline const CString& Indent::GetID() const
{ return m_strID; }

inline void Indent::ApplyChange()
{ m_bChanged=FALSE; }



// globals

extern Indent theIndent;
