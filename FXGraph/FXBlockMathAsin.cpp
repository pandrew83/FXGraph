#include "StdAfx.h"
#include "FXBlockMathAsin.h"
#include <math.h>
IMPLEMENT_SERIAL(CFXBlockMathAsin,CFXBlock,1);

CFXBlockMathAsin::CFXBlockMathAsin(void)
{
}

CFXBlockMathAsin::CFXBlockMathAsin(CFXBlock* pBlock):CFXBlock(pBlock){
	m_Name = "Asin(X)";
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

bool CFXBlockMathAsin::Calc(){
	if (!CFXBlock::Calc())
		return false;
	double x = m_InputPins.GetHead()->GetValue();
	m_OutputPins.GetHead()->SetValue( asin(x) );
	return true;
}

CFXBlockMathAsin::~CFXBlockMathAsin(void)
{
}
