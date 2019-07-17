#include "stdafx.h"
#include "CFXBlockMemoryLogical.h"
IMPLEMENT_SERIAL(CFXBlockMemoryLogical, CFXBlock, 1);

CFXBlockMemoryLogical::CFXBlockMemoryLogical()
{
}

CFXBlockMemoryLogical::~CFXBlockMemoryLogical()
{
}

bool CFXBlockMemoryLogical::Calc()
{
	if (!CFXBlock::Calc())
		return false;
	POSITION pos = m_InputPins.GetHeadPosition();
	bool x = m_InputPins.GetNext(pos)->GetValue();
	bool q = m_InputPins.GetNext(pos)->GetValue();
	if (q) {
		m_Memory = x;
	}
	m_OutputPins.GetHead()->SetValue(m_Memory);
	return true;
}

void CFXBlockMemoryLogical::Initialize()
{
	m_Memory = false;
}

void CFXBlockMemoryLogical::Create(CFXObject* pObject)
{
	CFXBlock::Create(pObject);
	m_Name = _T("Память");
	m_InputPinTypes.AddTail(Logical);
	m_OutputPinTypes.AddTail(Logical);
	m_PinInMinCount = 2;
	m_PinInMaxCount = 2;
	m_PinOutMinCount = 1;
	m_PinOutMaxCount = 1;
	AddInputPin(Logical, _T("X"));
	AddInputPin(Logical, _T("Q"));
	AddOutputPin(Logical, _T("Y"));
}
