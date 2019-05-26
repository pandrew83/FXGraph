#include "StdAfx.h"
#include "FXBlockMathExp.h"
#include <math.h>
IMPLEMENT_SERIAL(CFXBlockMathExp,CFXBlock,1);

CFXBlockMathExp::CFXBlockMathExp(void)
{
}

CFXBlockMathExp::CFXBlockMathExp(CFXBlock* pBlock):CFXBlock(pBlock){
	m_Name = "Exp";
	m_PinInMaxCount = 1;
	m_PinInMinCount = 1;
	m_PinOutMinCount = 1;
	m_PinOutMaxCount = 1;
	m_InputPinTypes.AddTail(Float);
	m_OutputPinTypes.AddTail(Float);
	AddInputPin(Float,_T("x"));
	AddOutputPin(Float,_T("z")); 
}

bool CFXBlockMathExp::Calc(){
	if (!CFXBlock::Calc())
		return false;
	double x = m_InputPins.GetHead()->GetValue();
	m_OutputPins.GetHead()->SetValue( exp(x) );
	return true;
}

CFXBlockMathExp::~CFXBlockMathExp(void)
{
}
