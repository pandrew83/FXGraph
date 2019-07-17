#include "stdafx.h"
#include "CFXBlockMathFloatLimits.h"
IMPLEMENT_SERIAL(CFXBlockMathFloatLimits, CFXBlock, 1);

CFXBlockMathFloatLimits::CFXBlockMathFloatLimits()
{
}

CFXBlockMathFloatLimits::~CFXBlockMathFloatLimits()
{
}

void CFXBlockMathFloatLimits::Create(CFXObject* pObject)
{
	CFXBlock::Create(pObject);
	m_Name = _T("Ограничения");
	m_MinHeight = 100;
	m_Height = 100;
	m_InputPinTypes.AddTail(Float);
	m_OutputPinTypes.AddTail(Float);
	m_PinInMinCount = 3;
	m_PinInMaxCount = 3;
	m_PinOutMinCount = 1;
	m_PinOutMaxCount = 1;
	AddInputPin(Float, _T("X"));
	AddInputPin(Float, _T("Min"));
	AddInputPin(Float, _T("Max"));
	AddOutputPin(Float, _T("Y"));
	m_Current = 0;
}

bool CFXBlockMathFloatLimits::Calc()
{
	if (!CFXBlock::Calc())
		return false;
	POSITION pos = m_InputPins.GetHeadPosition();
	double x = m_InputPins.GetNext(pos)->GetValue();
	double min = m_InputPins.GetNext(pos)->GetValue();
	double max = m_InputPins.GetNext(pos)->GetValue();
	if (min > x)
		m_Current = min;
	if (max < x)
		m_Current = max;
	if (min <= x && x <= max)
		m_Current = x;
	m_OutputPins.GetHead()->SetValue(m_Current);
}

void CFXBlockMathFloatLimits::Initialize()
{
	m_Current = 0;
}
