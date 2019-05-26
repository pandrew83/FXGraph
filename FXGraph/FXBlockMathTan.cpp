#include "StdAfx.h"
#include "FXBlockMathTan.h"
#include <math.h>
IMPLEMENT_SERIAL(CFXBlockMathTan,CFXBlock,1);

CFXBlockMathTan::CFXBlockMathTan(void)
{
}

CFXBlockMathTan::CFXBlockMathTan(CFXBlock* pBlock):CFXBlock(pBlock){
	m_Name = "Tan";
	m_PinInMaxCount = 1;
	m_PinInMinCount = 1;
	m_PinOutMinCount = 1;
	m_PinOutMaxCount = 1;
	m_InputPinTypes.AddTail(Float);
	m_OutputPinTypes.AddTail(Float);
	AddInputPin(Float,_T("x"));
	AddOutputPin(Float,_T("z"));
}

bool CFXBlockMathTan::Calc(){
	if (!CFXBlock::Calc())
		return false;
	double x = m_InputPins.GetHead()->GetValue();
	m_OutputPins.GetHead()->SetValue( tan(x) );
	return true;
}

CFXBlockMathTan::~CFXBlockMathTan(void)
{
}
