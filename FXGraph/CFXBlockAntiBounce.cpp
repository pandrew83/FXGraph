#include "stdafx.h"
#include "CFXBlockAntiBounce.h"

#define BLOCK_ANTIBOUNCE_TIMEOUT 10

CFXBlockAntiBounce::CFXBlockAntiBounce()
{
}

CFXBlockAntiBounce::CFXBlockAntiBounce(CFXBlock* pBlock) : CFXBlock(pBlock)
{
	m_Name = "Bounce";
	m_PinInMaxCount = 1;
	m_PinInMinCount = 1;
	m_PinOutMinCount = 1;
	m_PinOutMaxCount = 1;
	m_InputPinTypes.AddTail(Logical);
	m_OutputPinTypes.AddTail(Logical);
	AddInputPin(Float, _T("x"));
	AddOutputPin(Float, _T("z"));

}

CFXBlockAntiBounce::~CFXBlockAntiBounce()
{
}

bool CFXBlockAntiBounce::Calc()
{
	if (!CFXBlock::Calc())
		return false;
	bool x = m_InputPins.GetHead()->GetValue();
	if (m_Ticks == 0 && x) {
		m_Ticks = GetSysTicks();
	}
	if (GetSysTicks() - m_Ticks > BLOCK_ANTIBOUNCE_TIMEOUT) 
		m_OutputPins.GetHead()->SetValue(true);
	else {
		m_Ticks = 0;
		m_OutputPins.GetHead()->SetValue(false);
	}
	return true;
}
