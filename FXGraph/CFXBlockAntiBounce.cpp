#include "stdafx.h"
#include "CFXBlockAntiBounce.h"

// Это русский комментарий

IMPLEMENT_SERIAL(CFXBlockAntiBounce, CFXBlock, 1);
CFXBlockAntiBounce::CFXBlockAntiBounce()
{
	m_Ticks = 0;
}

CFXBlockAntiBounce::CFXBlockAntiBounce(CFXBlock* pBlock) : CFXBlock(pBlock)
{
	m_Name = "Bounce";
	m_PinInMaxCount = 2;
	m_PinInMinCount = 2;
	m_PinOutMinCount = 1;
	m_PinOutMaxCount = 1;
	m_InputPinTypes.AddTail(Logical);
	m_InputPinTypes.AddTail(Int);
	m_OutputPinTypes.AddTail(Logical);
	AddInputPin(Logical, _T("x"));
	AddInputPin(Int, _T("Timeout"));
	AddOutputPin(Logical, _T("z"));
	m_Ticks = 0;
}

CFXBlockAntiBounce::~CFXBlockAntiBounce()
{
}

bool CFXBlockAntiBounce::Calc()
{
	if (!CFXBlock::Calc())
		return false;
	POSITION pos = m_InputPins.GetHeadPosition();
	bool x = m_InputPins.GetNext(pos)->GetValue();
	int timeout = m_InputPins.GetNext(pos)->GetValue();
	if (m_Ticks == 0 && x) {
		m_Ticks = GetSysTicks();
	}
	if (GetSysTicks() - m_Ticks > timeout) 
		m_OutputPins.GetHead()->SetValue(true);
	else {
		m_Ticks = 0;
		m_OutputPins.GetHead()->SetValue(false);
	}
	return true;
}
