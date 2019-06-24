#include "stdafx.h"
#include "CFXBlockTransformCurrent.h"
IMPLEMENT_SERIAL(CFXBlockTransformCurrent, CFXBlock, 1);

CFXBlockTransformCurrent::CFXBlockTransformCurrent()
{
}

void CFXBlockTransformCurrent::Create(CFXObject* pObject) 
{
	CFXBlock::Create(pObject);
	m_PinInMinCount = 1;
	m_PinOutMinCount = 1;
	m_PinOutMaxCount = 1;
	m_InputPinTypes.AddTail(Float);
	m_OutputPinTypes.AddTail(Float);
	AddInputPin(Float, _T("x"));
	AddOutputPin(Float, _T("z"));
}

bool CFXBlockTransformCurrent::Calc()
{
	if (!CFXBlock::Calc())
		return false;
	double x = m_InputPins.GetHead()->GetValue();
	double z = x * (double)0.02 / (double)3.2;
	m_OutputPins.GetHead()->SetValue(z);
	return true;
}
