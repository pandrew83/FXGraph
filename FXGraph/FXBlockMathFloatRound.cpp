#include "StdAfx.h"
#include "FXBlockMathFloatRound.h"
#include <cmath>
#include <math.h>

IMPLEMENT_SERIAL(CFXBlockMathFloatRound,CFXBlock,1);

CFXBlockMathFloatRound::CFXBlockMathFloatRound(void)
{
}

void CFXBlockMathFloatRound::Create(CFXObject* pObject)
{
	CFXBlock::Create(pObject);
	m_Name = "Round(X)";
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

bool CFXBlockMathFloatRound::Calc(){
	if (!CFXBlock::Calc())
		return false;
	double x = m_InputPins.GetHead()->GetValue();
	double i;
	double f = modf(x,&i);
	if (i >=0){
		m_OutputPins.GetHead()->SetValue( f>(double)0.5?f+1:f );
	}
	else{
		m_OutputPins.GetHead()->SetValue( f>(double)0.5?f-1:f);
	}
	return true;
}

CFXBlockMathFloatRound::~CFXBlockMathFloatRound(void)
{
}
