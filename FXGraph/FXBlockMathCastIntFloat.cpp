#include "StdAfx.h"
#include "FXBlockMathCastIntFloat.h"
IMPLEMENT_SERIAL(CFXBlockMathCastIntFloat,CFXBlock,1);


CFXBlockMathCastIntFloat::CFXBlockMathCastIntFloat(void)
{
}


CFXBlockMathCastIntFloat::~CFXBlockMathCastIntFloat(void)
{
}

CFXBlockMathCastIntFloat::CFXBlockMathCastIntFloat(CFXBlock* pBlock) :CFXBlock(pBlock) {
	m_Name = "Int2Float";
	m_MinHeight = m_Height = 50;
	m_PinInMinCount = 1;
	m_PinInMaxCount = 1;
	m_PinOutMinCount = 1;
	m_PinOutMaxCount = 1;
	m_InputPinTypes.AddTail(Int);
	m_OutputPinTypes.AddTail(Float);

	AddInputPin(Int, _T("x"));
	AddOutputPin(Float, _T("z"));
}

bool CFXBlockMathCastIntFloat::Calc(void)
{
	if (!CFXBlock::Calc())
		return false;
	ASSERT(m_InputPins.GetCount() == 1 && m_OutputPins.GetCount() == 1);
	CFXPin* pPinIn = m_InputPins.GetHead();
	CFXPin* pPinOut = m_OutputPins.GetHead();
	pPinOut->SetValue( (double)pPinIn->GetValue());
	return true;
}
