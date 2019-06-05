#include "StdAfx.h"
#include "FXBlockMathLog10.h"
#include <math.h>
IMPLEMENT_SERIAL(CFXBlockMathLog10,CFXBlock,1);

CFXBlockMathLog10::CFXBlockMathLog10(void)
{
}

CFXBlockMathLog10::CFXBlockMathLog10(CFXBlock* pBlock):CFXBlock(pBlock){
	m_Name = "Log10(X)";
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

bool CFXBlockMathLog10::Calc(){
	if (!CFXBlock::Calc())
		return false;
	double x = m_InputPins.GetHead()->GetValue();
	m_OutputPins.GetHead()->SetValue( log10(x) );
	return true;
}

CFXBlockMathLog10::~CFXBlockMathLog10(void)
{
}
