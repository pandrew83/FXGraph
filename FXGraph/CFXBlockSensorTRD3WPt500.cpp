﻿#include "stdafx.h"
#include "CFXBlockSensorTRD3WPt500.h"
IMPLEMENT_SERIAL(CFXBlockSensorTRD3WPt500, CFXBlock, 1);

#define BLOCK_SENSOR_TRD_W2_M50_CURRENT		(double)0.001
#define BLOCK_SENSOR_TRD_W2_M50_MULTIPLIER	(double)35

CFXBlockSensorTRD3WPt500::CFXBlockSensorTRD3WPt500()
{
}

void CFXBlockSensorTRD3WPt500::Create(CFXObject* pBlock)
{
	CFXBlock::Create(pBlock);
	m_Name = "TRD 3W Pt500";
	m_PinInMaxCount = 1;
	m_PinInMinCount = 1;
	m_PinOutMinCount = 1;
	m_PinOutMaxCount = 1;
	m_InputPinTypes.AddTail(Float);
	m_OutputPinTypes.AddTail(Float);
	AddInputPin(Float, _T("x"));
	AddOutputPin(Float, _T("z"));
}

bool CFXBlockSensorTRD3WPt500::Calc()
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
