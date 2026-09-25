
#pragma once


class Doc : public CDocument
{
	DECLARE_DYNCREATE(Doc)

protected:
	Doc();

public:
	virtual ~Doc();

protected:
	DECLARE_MESSAGE_MAP()
};
