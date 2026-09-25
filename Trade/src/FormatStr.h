
#pragma once


class FormatStr : public CString
{
public:
	enum Type { typeLoad, typeCtrl, typeStore };
	enum Part { partDateTime, partDate, partTime, PartCount };

public:
	FormatStr(Type type, Part part);
	virtual ~FormatStr();
};
