#include "StdAfx.h"
#include "FXParam.h"
IMPLEMENT_SERIAL(CFXParam,CObject,1);

CFXParam::CFXParam(void)
	: m_pPin(NULL)
{
}


CFXParam::~CFXParam(void)
{
}


void CFXParam::Serialize(CArchive& ar)
{
	bool bVal;
	int iVal;
	double dVal;
	if (ar.IsStoring()){
		ar << m_Name;
		ar << m_Type;
		switch(m_Type){
			case Logical:
				ar << (bool)m_Value;
				break;
			case Int:
				ar << (int)m_Value;
				break;
			case Float:
				ar << (double)m_Value;
				break;
		}
	}
	else{
		ar >> m_Name;
		ar >> m_Type;
		switch(m_Type){
			case Logical:
//				m_Value.vt = VT_BOOL;
				ar >> bVal;
				m_Value = bVal;
				break;
			case Int:
				ar >> iVal;
				m_Value = iVal;
				break;
			case Float:
				ar >> dVal;
				m_Value = dVal;
				break;
		}
	}
}
