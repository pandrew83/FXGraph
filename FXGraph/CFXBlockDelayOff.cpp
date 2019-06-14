#include "stdafx.h"
#include "CFXBlockDelayOff.h"
IMPLEMENT_SERIAL(CFXBlockDelayOff, CFXBlock, 1);
// Это русский комментарий

CFXBlockDelayOff::CFXBlockDelayOff()
{
	m_Ticks = 0;
}

CFXBlockDelayOff::CFXBlockDelayOff(CFXBlock* pBlock) : CFXBlock(pBlock)
{
	m_Name = "Delay Off";
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

CFXBlockDelayOff::~CFXBlockDelayOff()
{
}

bool CFXBlockDelayOff::Calc()
{
	if (!CFXBlock::Calc())
		return false;
	POSITION pos = m_InputPins.GetHeadPosition();
	bool x = m_InputPins.GetNext(pos)->GetValue();
	int delay = m_InputPins.GetNext(pos)->GetValue();
	CFXPin* pPin = m_OutputPins.GetHead();
	if (x) {
		pPin->SetValue(true);
		m_Ticks = 0;
	}
	else
		if (!x && !m_Ticks) {
			m_Ticks = GetSysTicks();
		}
		else
			if (!x && GetSysTicks() - m_Ticks >= delay) {
				pPin->SetValue(false);
			}
	return true;
}
