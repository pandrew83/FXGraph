#include "StdAfx.h"
#include "FXBlockMathCastIntFloat.h"
IMPLEMENT_SERIAL(CFXBlockMathCastIntFloat,CFXBlock,1);


CFXBlockMathCastIntFloat::CFXBlockMathCastIntFloat(void)
{
}


CFXBlockMathCastIntFloat::~CFXBlockMathCastIntFloat(void)
{
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
