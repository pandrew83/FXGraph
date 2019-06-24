#include "StdAfx.h"
#include "FXBlockMathAcos.h"
#include <math.h>
IMPLEMENT_SERIAL(CFXBlockMathAcos,CFXBlock,1);

CFXBlockMathAcos::CFXBlockMathAcos(void)
{
}

void CFXBlockMathAcos::Create(CFXObject* pObject)
{
	CFXBlock::Create(pObject);
	m_Name = "Acos(X)";
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

bool CFXBlockMathAcos::Calc(){
	if (!CFXBlock::Calc())
		return false;
	double x = m_InputPins.GetHead()->GetValue();
	m_OutputPins.GetHead()->SetValue( acos(x) );
	return true;
}

CFXBlockMathAcos::~CFXBlockMathAcos(void)
{
}
