#pragma once
#include "FXPin.h"

class CFXParam : public CObject {
public:
	DECLARE_SERIAL(CFXParam);
	CString m_Name;
	CFXPinType m_Type;
	CFXParam();
	CFXParam(CString name, CFXPinType type,variant_t value){
		m_Name = name;
		m_Type = type;
		m_pPin = NULL;
		m_Value = value;
	}
	~CFXParam();
	void Serialize(CArchive& ar);
	variant_t m_Value;
	CFXPin* m_pPin;
};

typedef CList<CFXParam,CFXParam&> CListParam;