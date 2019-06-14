#include "stdafx.h"
#include "CFXBlockSensorTRD4WPt100.h"
IMPLEMENT_SERIAL(CFXBlockSensorTRD4WPt100, CFXBlock, 1);

#define BLOCK_SENSOR_TRD_W2_M50_CURRENT		(double)0.001
#define BLOCK_SENSOR_TRD_W2_M50_MULTIPLIER	(double)35

CFXBlockSensorTRD4WPt100::CFXBlockSensorTRD4WPt100()
{
}

CFXBlockSensorTRD4WPt100::CFXBlockSensorTRD4WPt100(CFXBlock* pBlock) : CFXBlock(pBlock)
{
	m_Name = "TRD 4W Pt100";
	m_PinInMaxCount = 1;
	m_PinInMinCount = 1;
	m_PinOutMinCount = 1;
	m_PinOutMaxCount = 1;
	m_InputPinTypes.AddTail(Float);
	m_OutputPinTypes.AddTail(Float);
	AddInputPin(Float, _T("x"));
	AddOutputPin(Float, _T("z"));
}

bool CFXBlockSensorTRD4WPt100::Calc()
{
	if (!CFXBlock::Calc())
		return false;
	POSITION pos = m_InputPins.GetHeadPosition();
	double x = m_InputPins.GetNext(pos)->GetValue();
	// TODO: –еализовать расчет температуры
	double y = x;
	m_OutputPins.GetHead()->SetValue(y);
	return true;
}
