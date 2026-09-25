
#include "stdafx.h"
#include "FormatStr.h"
#include "resource.h"


FormatStr::FormatStr(Type type, Part part)
{
	if(type!=typeStore)
		LoadString(IDS_FORMAT_LOAD_DT+type*PartCount+part);

	if(IsEmpty())
	{
		switch(type)
		{
		case typeLoad:
			switch(part)
			{
			case partDateTime: SetString(_T("%Y.%m.%d %H:%M:%S")); break;
			case partDate: SetString(_T("%Y.%m.%d")); break;
			case partTime: SetString(_T("%H:%M:%S")); break;
			}
			break;

		case typeStore:
			switch(part)
			{
			case partDateTime: SetString(_T("%Y-%m-%d %H:%M:%S")); break;
			case partDate: SetString(_T("%Y-%m-%d")); break;
			case partTime: SetString(_T("%H:%M:%S")); break;
			}
			break;

		case typeCtrl:
			switch(part)
			{
			case partDateTime: SetString(_T("yyyy'.'MM'.'dd HH':'mm':'ss")); break;
			case partDate: SetString(_T("yyyy'.'MM'.'dd")); break;
			case partTime: SetString(_T("HH':'mm':'ss")); break;
			}
			break;

		//case typeReport:
		//	switch(part)
		//	{
		//	case partDateTime: SetString(_T("%Y.%m.%d %H:%i:%s")); break;
		//	case partDate: SetString(_T("%Y.%m.%d")); break;
		//	case partTime: SetString(_T("%H:%i:%s")); break;
		//	}
		//	break;
		}
	}
}

FormatStr::~FormatStr()
{
}
