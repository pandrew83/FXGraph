#include "StdAfx.h"
#include "FXBlockMathSqrt.h"
#include <math.h>
IMPLEMENT_SERIAL(CFXBlockMathSqrt,CFXBlock,1);

CFXBlockMathSqrt::CFXBlockMathSqrt(void)
{
}

CFXBlockMathSqrt::CFXBlockMathSqrt(CFXBlock* pBlock):CFXBlock(pBlock){
	m_Name = "Sqrt(X)";
	m_MinHeight = m_Height = 50;
	m_PinInMaxCount = 1;
	m_PinInMinCount = 1;
	m_PinOutMinCount = 1;
	m_PinOutMaxCount = 1;
	m_InputPinTypes.AddTail(Float);
	m_OutputPinTypes.AddTail(Float);
	AddInputPin(Float,_T("x"));
	AddOutputPin(Float,_T("z"));
}

bool CFXBlockMathSqrt::Calc(){
	if (!CFXBlock::Calc())
		return false;
	double x = m_InputPins.GetHead()->GetValue();
	m_OutputPins.GetHead()->SetValue( sqrt(x) );
	return true;
}

CFXBlockMathSqrt::~CFXBlockMathSqrt(void)
{
}
