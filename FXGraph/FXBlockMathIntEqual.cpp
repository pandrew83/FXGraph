#include "StdAfx.h"
#include "FXBlockMathIntEqual.h"
IMPLEMENT_SERIAL(CFXBlockMathIntEqual,CFXBlock,1);

CFXBlockMathIntEqual::CFXBlockMathIntEqual(void)
{
}

void CFXBlockMathIntEqual::Create(CFXObject* pObject)
{
	CFXBlock::Create(pObject);
	m_Name = "X == Y";
	m_PinInMaxCount = 2;
	m_PinInMinCount = 2;
	m_PinOutMinCount = 2;
	m_PinOutMaxCount = 2;
	m_InputPinTypes.AddTail(Int);
	m_OutputPinTypes.AddTail(Logical);
	AddInputPin(Int,_T("x"));
	AddInputPin(Int,_T("y"));
	AddOutputPin(Logical,_T("z"));
	AddOutputPin(Logical,_T("~z"));
}

bool CFXBlockMathIntEqual::Calc(){
	if (!CFXBlock::Calc())
		return false;
	POSITION pos = m_InputPins.GetHeadPosition();
	int x = m_InputPins.GetNext(pos)->GetValue();
	int y = m_InputPins.GetNext(pos)->GetValue();
	pos = m_OutputPins.GetHeadPosition();
	m_OutputPins.GetNext(pos)->SetValue( x == y);
	m_OutputPins.GetNext(pos)->SetValue( x != y);
	return true;
}

CFXBlockMathIntEqual::~CFXBlockMathIntEqual(void)
{
}
