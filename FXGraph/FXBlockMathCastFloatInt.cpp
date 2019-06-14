#include "StdAfx.h"
#include "FXBlockMathCastFloatInt.h"
IMPLEMENT_SERIAL(CFXBlockMathCastFloatInt,CFXBlock,1);


CFXBlockMathCastFloatInt::CFXBlockMathCastFloatInt(void)
{
}

CFXBlockMathCastFloatInt::CFXBlockMathCastFloatInt(CFXBlock* pBlock) :CFXBlock(pBlock) {
	m_Name = "Float2Int";
	m_MinHeight = m_Height = 50;
	m_PinInMinCount = 1;
	m_PinInMaxCount = 1;
	m_PinOutMinCount = 1;
	m_PinOutMaxCount = 1;
	m_InputPinTypes.AddTail(Float);
	m_OutputPinTypes.AddTail(Int);

	AddInputPin(Float, _T("x"));
	AddOutputPin(Int, _T("z"));
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
