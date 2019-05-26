#pragma once
#include "afx.h"
class CFXException :
	public CException
{
public:
	CFXException(void);
	CFXException(CString msg){
		m_Msg = msg;
	}
	~CFXException(void);
	CString m_Msg;
};

