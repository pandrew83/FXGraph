#include "StdAfx.h"
#include "FXBlockMathIntAbs.h"
IMPLEMENT_SERIAL(CFXBlockMathIntAbs,CFXBlock,1);

CFXBlockMathIntAbs::CFXBlockMathIntAbs(void)
{
}

void CFXBlockMathIntAbs::Create(CFXObject* pObject)
{
	CFXBlock::Create(pObject);
	m_Name = "Abs(X)";
	m_MinHeight = m_Height = 50;
	m_PinInMinCount = 1;
	m_PinInMaxCount = 1;
	m_PinOutMinCount = 1;
	m_PinOutMaxCount = 1;
	m_InputPinTypes.AddTail(Int);
	m_OutputPinTypes.AddTail(Int);
	AddInputPin(Int,_T("x"));
	AddOutputPin(Int,_T("z"));
}

bool CFXBlockMathIntAbs::Calc(){
	if (CFXBlock::Calc())
		return false;
	int x = m_InputPins.GetHead()->GetValue();
	m_OutputPins.GetHead()->SetValue( abs(x) );
	return true;
}

CFXBlockMathIntAbs::~CFXBlockMathIntAbs(void)
{
}
