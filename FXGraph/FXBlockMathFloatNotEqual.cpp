#include "StdAfx.h"
#include "FXBlockMathFloatNotEqual.h"
IMPLEMENT_SERIAL(CFXBlockMathFloatNotEqual,CFXBlock,1);

CFXBlockMathFloatNotEqual::CFXBlockMathFloatNotEqual(void)
{
}

void CFXBlockMathFloatNotEqual::Create(CFXObject* pObject)
{
	CFXBlock::Create(pObject);
	m_Name = "X != Y";
	m_PinInMinCount = 2;
	m_PinInMaxCount = 32;
	m_PinOutMinCount = 1;
	m_PinOutMaxCount = 1;
	m_InputPinTypes.AddTail(Float);
	m_OutputPinTypes.AddTail(Logical);
	AddInputPin(Float,_T("x"));
	AddInputPin(Float,_T("y"));
	AddOutputPin(Logical,_T("z"));
}

CFXBlockMathFloatNotEqual::~CFXBlockMathFloatNotEqual(void)
{
}


bool CFXBlockMathFloatNotEqual::Calc(void)
{
	if (!CFXBlock::Calc())
		return false;
	POSITION pos = m_InputPins.GetHeadPosition();
	CFXPin* pPin1 = m_InputPins.GetNext(pos);
	CFXPin* pPin2 = m_InputPins.GetNext(pos);
	CFXPin* pPinOut = m_OutputPins.GetHead();
	pPinOut->SetValue( (double)pPin1->GetValue() != (double)pPin2->GetValue() );
	return true;
}
