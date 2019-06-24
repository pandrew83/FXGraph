#include "stdafx.h"
#include "CFXBlockDelayOn.h"
IMPLEMENT_SERIAL(CFXBlockDelayOn, CFXBlock, 1);

CFXBlockDelayOn::CFXBlockDelayOn()
{
	m_Ticks = 0;
}

void CFXBlockDelayOn::Create(CFXObject* pObject)
{
	CFXBlock::Create(pObject);
	m_Name = "Delay On";
	m_PinInMaxCount = 2;
	m_PinInMinCount = 2;
	m_PinOutMinCount = 1;
	m_PinOutMaxCount = 1;
	m_InputPinTypes.AddTail(Logical);
	m_InputPinTypes.AddTail(Int);
	m_OutputPinTypes.AddTail(Logical);
	AddInputPin(Logical, _T("x"));
	AddInputPin(Int, _T("Delay"));
	AddOutputPin(Logical, _T("z"));
	m_Ticks = 0;
}

CFXBlockDelayOn::~CFXBlockDelayOn()
{
}

bool CFXBlockDelayOn::Calc()
{
	if (!CFXBlock::Calc())
		return false;
	POSITION pos = m_InputPins.GetHeadPosition();
	bool x = m_InputPins.GetNext(pos)->GetValue();
	int delay = m_InputPins.GetNext(pos)->GetValue();
	if (!m_Ticks && x) {
		m_Ticks = GetSysTicks();
	}
	if (m_Ticks && x && GetSysTicks() - m_Ticks >= delay) {
		m_OutputPins.GetHead()->SetValue(true);
	}
	if (!x) {
		m_Ticks = 0;
		m_OutputPins.GetHead()->SetValue(false);
	}
	
	return false;
}
