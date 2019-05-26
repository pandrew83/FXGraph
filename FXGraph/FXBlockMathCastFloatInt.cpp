#include "StdAfx.h"
#include "FXBlockMathCastFloatInt.h"
IMPLEMENT_SERIAL(CFXBlockMathCastFloatInt,CFXBlock,1);


CFXBlockMathCastFloatInt::CFXBlockMathCastFloatInt(void)
{
}


CFXBlockMathCastFloatInt::~CFXBlockMathCastFloatInt(void)
{
}


bool CFXBlockMathCastFloatInt::Calc(void)
{
	if (!CFXBlock::Calc())
		return false;
	ASSERT(m_InputPins.GetCount() == 1 && m_OutputPins.GetCount() == 1);
	CFXPin* pPinIn = m_InputPins.GetHead();
	CFXPin* pPinOut = m_OutputPins.GetHead();
	double dbl = (double)pPinIn->GetValue();
	int value = (int)dbl;
	pPinOut->SetValue( value );
	return true;
}
