#include "StdAfx.h"
#include "FXBlockMathFloatMul.h"
IMPLEMENT_SERIAL(CFXBlockMathFloatMul,CFXBlock,1);


CFXBlockMathFloatMul::CFXBlockMathFloatMul(void)
{
}

CFXBlockMathFloatMul::CFXBlockMathFloatMul(CFXBlock* pBlock):CFXBlock(pBlock){
	m_Name = "X * Y";
	m_PinInMinCount = 2;
	m_PinInMaxCount = 32;
	m_PinOutMinCount = 1;
	m_PinOutMaxCount = 1;
	m_InputPinTypes.AddTail(Float);
	m_OutputPinTypes.AddTail(Float);
	AddInputPin(Float,_T("x"));
	AddInputPin(Float,_T("y"));
	AddOutputPin(Float,_T("z"));
}

CFXBlockMathFloatMul::~CFXBlockMathFloatMul(void)
{
}


bool CFXBlockMathFloatMul::Calc(void)
{
	if (!CFXBlock::Calc())
		return false;
	ASSERT(m_InputPins.GetCount() == 2 && m_OutputPins.GetCount() == 1);

	POSITION pos = m_InputPins.GetHeadPosition();
	CFXPin* pPin1 = m_InputPins.GetNext(pos);
	CFXPin* pPin2 = m_InputPins.GetNext(pos);
	CFXPin* pPinOut = m_OutputPins.GetHead();
	pPinOut->SetValue( (double)pPin1->GetValue() * (double)pPin2->GetValue() );
	return true;
}
