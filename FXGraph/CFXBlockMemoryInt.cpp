#include "stdafx.h"
#include "CFXBlockMemoryInt.h"
IMPLEMENT_SERIAL(CFXBlockMemoryInt, CFXBlock, 1);

CFXBlockMemoryInt::CFXBlockMemoryInt()
{
}

CFXBlockMemoryInt::~CFXBlockMemoryInt()
{
}

bool CFXBlockMemoryInt::Calc()
{
	if (!CFXBlock::Calc())
		return false;
	POSITION pos = m_InputPins.GetHeadPosition();
	int x = m_InputPins.GetNext(pos)->GetValue();
	bool q = m_InputPins.GetNext(pos)->GetValue();
	if (q) {
		m_Memory = x;
	}
	m_OutputPins.GetHead()->SetValue(m_Memory);
	return true;
}

void CFXBlockMemoryInt::Initialize()
{
	m_Memory = 0;
}

void CFXBlockMemoryInt::Create(CFXObject* pObject)
{
	CFXBlock::Create(pObject);
	m_Name = _T("Память");
	m_InputPinTypes.AddTail(Int);
	m_InputPinTypes.AddTail(Logical);
	m_OutputPinTypes.AddTail(Int);
	m_PinInMinCount = 2;
	m_PinInMaxCount = 2;
	m_PinOutMinCount = 1;
	m_PinOutMaxCount = 1;
	AddInputPin(Int, _T("X"));
	AddInputPin(Logical, _T("Q"));
	AddOutputPin(Int, _T("Y"));
}
