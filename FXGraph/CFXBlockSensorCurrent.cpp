#include "stdafx.h"
#include "CFXBlockSensorCurrent.h"
IMPLEMENT_SERIAL(CFXBlockSensorCurrent, CFXBlock, 1);

CFXBlockSensorCurrent::CFXBlockSensorCurrent()
{
}

CFXBlockSensorCurrent::CFXBlockSensorCurrent(CFXBlock* pBlock) : CFXBlock(pBlock)
{
	m_Name = "Current";
	m_PinInMaxCount = 1;
	m_PinInMinCount = 1;
	m_PinOutMinCount = 1;
	m_PinOutMaxCount = 1;
	m_InputPinTypes.AddTail(Float);
	m_OutputPinTypes.AddTail(Float);
	AddInputPin(Float, _T("x"));
	AddOutputPin(Float, _T("z"));
}

bool CFXBlockSensorCurrent::Calc()
{
	if (!CFXBlock::Calc())
		return false;
	double x = m_InputPins.GetHead()->GetValue();
	double z = x * (double)0.02 / (double)3.2;
	m_OutputPins.GetHead()->SetValue(z);
	return true;
}
