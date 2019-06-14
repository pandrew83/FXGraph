#include "StdAfx.h"
#include "FXBlockMathSin.h"
#include <math.h>

IMPLEMENT_SERIAL(CFXBlockMathSin,CFXBlock,1);

CFXBlockMathSin::CFXBlockMathSin(void)
{
}

CFXBlockMathSin::CFXBlockMathSin(CFXBlock* pBlock):CFXBlock(pBlock){
	m_Name = "Sin(X)";
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

bool CFXBlockMathSin::Calc(){
	if (!CFXBlock::Calc())
		return false;
	double x = m_InputPins.GetHead()->GetValue();
	m_OutputPins.GetHead()->SetValue( sin(x) );
	return true;
}

CFXBlockMathSin::~CFXBlockMathSin(void)
{
}
