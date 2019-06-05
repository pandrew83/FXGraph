#include "StdAfx.h"
#include "FXBlockMathPow.h"
#include <math.h>
IMPLEMENT_SERIAL(CFXBlockMathPow,CFXBlock,1);

CFXBlockMathPow::CFXBlockMathPow(void)
{
}

CFXBlockMathPow::CFXBlockMathPow(CFXBlock* pBlock):CFXBlock(pBlock){
	m_Name = "Pow(X,Y)";
	m_PinInMaxCount = 2;
	m_PinInMinCount = 2;
	m_PinOutMinCount = 1;
	m_PinOutMaxCount = 1;
	m_InputPinTypes.AddTail(Float);
	m_OutputPinTypes.AddTail(Float);
	AddInputPin(Float,_T("x"));
	AddInputPin(Float,_T("y"));
	AddOutputPin(Float,_T("z")); 
}

bool CFXBlockMathPow::Calc(){
	if (!CFXBlock::Calc())
		return false;
	POSITION pos = m_InputPins.GetHeadPosition();
	double x = m_InputPins.GetNext(pos)->GetValue();
	double y = m_InputPins.GetNext(pos)->GetValue();
	m_OutputPins.GetHead()->SetValue( pow(x,y) );
	return true;
}

CFXBlockMathPow::~CFXBlockMathPow(void)
{
}
