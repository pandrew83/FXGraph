#include "StdAfx.h"
#include "FXBlockMathLog.h"
#include <math.h>
IMPLEMENT_SERIAL(CFXBlockMathLog,CFXBlock,1);

CFXBlockMathLog::CFXBlockMathLog(void)
{
}

CFXBlockMathLog::CFXBlockMathLog(CFXBlock* pBlock):CFXBlock(pBlock){
	m_Name = "Log(X)";
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

bool CFXBlockMathLog::Calc(){
	if (!CFXBlock::Calc())
		return false;
	double x = m_InputPins.GetHead()->GetValue();
	m_OutputPins.GetHead()->SetValue( log(x) );
	return true;
}

CFXBlockMathLog::~CFXBlockMathLog(void)
{
}
