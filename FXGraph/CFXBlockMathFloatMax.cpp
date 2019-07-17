#include "stdafx.h"
#include "CFXBlockMathFloatMax.h"
IMPLEMENT_SERIAL(CFXBlockMathFloatMax, CFXBlock, 1);

CFXBlockMathFloatMax::CFXBlockMathFloatMax()
{
}

CFXBlockMathFloatMax::~CFXBlockMathFloatMax()
{
}

bool CFXBlockMathFloatMax::Calc()
{
	if (!CFXBlock::Calc())
		return false;
	double max = m_InputPins.GetHead()->GetValue();
	POSITION pos = m_InputPins.GetHeadPosition();
	while (pos) {
		double v = m_InputPins.GetNext(pos)->GetValue();
		if (max < v)
			max = v;
	}
	m_OutputPins.GetHead()->SetValue(max);
	return true;
}

void CFXBlockMathFloatMax::Create(CFXObject* pObject)
{
	CFXBlock::Create(pObject);
	m_Name = _T("Максимум");
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
