#include "StdAfx.h"
#include "FXBlockMathAtan.h"
#include <math.h>
IMPLEMENT_SERIAL(CFXBlockMathAtan,CFXBlock,1);

CFXBlockMathAtan::CFXBlockMathAtan(void)
{
}

CFXBlockMathAtan::CFXBlockMathAtan(CFXBlock* pBlock):CFXBlock(pBlock){
	m_Name = "Atan(X)";
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

bool CFXBlockMathAtan::Calc(){
	if (!CFXBlock::Calc())
		return false;
	double x = m_InputPins.GetHead()->GetValue();
	m_OutputPins.GetHead()->SetValue( atan(x) );
	return true;
}

CFXBlockMathAtan::~CFXBlockMathAtan(void)
{
}
