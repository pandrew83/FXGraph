#include "stdafx.h"
#include "CFXBlockMemoryFloat.h"
IMPLEMENT_SERIAL(CFXBlockMemoryFloat, CFXBlock, 1);

CFXBlockMemoryFloat::CFXBlockMemoryFloat()
{
}

CFXBlockMemoryFloat::~CFXBlockMemoryFloat()
{
}

bool CFXBlockMemoryFloat::Calc()
{
	if (!CFXBlock::Calc())
		return false;
	POSITION pos = m_InputPins.GetHeadPosition();
	double x = m_InputPins.GetNext(pos)->GetValue();
	bool q = m_InputPins.GetNext(pos)->GetValue();
	if (q) {
		m_Memory = x;
	}
	m_OutputPins.GetHead()->SetValue(m_Memory);
	return true;
}

void CFXBlockMemoryFloat::Create(CFXObject* pObject)
{
	CFXBlock::Create(pObject);
	m_Name = _T("Память");
	m_InputPinTypes.AddTail(Float);
	m_InputPinTypes.AddTail(Logical);
	m_OutputPinTypes.AddTail(Float);
	m_PinInMinCount = 2;
	m_PinInMaxCount = 2;
	m_PinOutMinCount = 1;
	m_PinOutMaxCount = 1;
	AddInputPin(Float, _T("X"));
	AddInputPin(Logical, _T("Q"));
	AddOutputPin(Float, _T("Y"));
}

void CFXBlockMemoryFloat::Initialize()
{
	m_Memory = 0;
}
