#include "StdAfx.h"
#include "FXBlockMathFloatAbs.h"
#include <math.h>

IMPLEMENT_SERIAL(CFXBlockMathFloatAbs,CFXBlock,1);

CFXBlockMathFloatAbs::CFXBlockMathFloatAbs(void)
{
}

void CFXBlockMathFloatAbs::Create(CFXObject* pObject)
{
	CFXBlock::Create(pObject);
	m_Name = "Abs(X)";
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

bool CFXBlockMathFloatAbs::Calc(){
	if (!CFXBlock::Calc())
		return false;
	double x = m_InputPins.GetHead()->GetValue();
	CFXPin* pin_z = m_OutputPins.GetHead();
	pin_z->SetValue( fabs(x));
	return true;
}

CFXBlockMathFloatAbs::~CFXBlockMathFloatAbs(void)
{
}
