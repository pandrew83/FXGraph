#include "stdafx.h"
#include "CFXBlockMathFloatMin.h"
IMPLEMENT_SERIAL(CFXBlockMathFloatMin, CFXBlock, 1);

CFXBlockMathFloatMin::CFXBlockMathFloatMin()
{
}

CFXBlockMathFloatMin::~CFXBlockMathFloatMin()
{
}

bool CFXBlockMathFloatMin::Calc()
{
	if (!CFXBlock::Calc())
		return false;
	double min = m_InputPins.GetHead()->GetValue();
	POSITION pos = m_InputPins.GetHeadPosition();
	while (pos) {
		double v = m_InputPins.GetNext(pos)->GetValue();
		if (min > v)
			min = v;
	}
	m_OutputPins.GetHead()->SetValue(min);
	return true;
}

void CFXBlockMathFloatMin::Create(CFXObject* pObject)
{
	CFXBlock::Create(pObject);
	m_Name = _T("Минимум");
	m_InputPinTypes.AddTail(Float);
	m_OutputPinTypes.AddTail(Float);
	m_PinInMinCount = 2;
	m_PinInMaxCount = 32;
	m_PinOutMinCount = 1;
	m_PinOutMaxCount = 1;
	AddInputPin(Float, _T("X1"));
	AddInputPin(Float, _T("X2"));
	AddOutputPin(Float, _T("Y"));
}
