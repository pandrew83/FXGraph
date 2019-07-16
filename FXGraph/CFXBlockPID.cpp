#include "stdafx.h"
#include "CFXBlockPID.h"

IMPLEMENT_SERIAL(CFXBlockPID, CFXBlock, 1);

CFXBlockPID::CFXBlockPID() {
}

CFXBlockPID::~CFXBlockPID() {
}

void CFXBlockPID::Create(CFXObject* pObject)
{
	CFXBlock::Create(pObject);
	m_MinHeight = 150;
	m_Height = 150;
	m_Name = _T("PID");
	m_PinInMaxCount = 5;
	m_PinInMinCount = 5;
	m_PinOutMaxCount = 1;
	m_PinOutMinCount = 1;
	m_InputPinTypes.AddTail(Float);
	m_OutputPinTypes.AddTail(Float);
	AddInputPin(Float, _T("Input"));
	AddInputPin(Float, _T("Target"));
	AddInputPin(Float, _T("Kp"));
	AddInputPin(Float, _T("Ki"));
	AddInputPin(Float, _T("Kd"));
	AddOutputPin(Float, _T("Output"));
}

bool CFXBlockPID::Calc()
{
	if (!CFXBlock::Calc())
		return false;
	POSITION pos = m_InputPins.GetHeadPosition();
	double input = m_InputPins.GetNext(pos)->GetValue();
	double target = m_InputPins.GetNext(pos)->GetValue();
	double kp = m_InputPins.GetNext(pos)->GetValue();
	double ki = m_InputPins.GetNext(pos)->GetValue();
	double kd = m_InputPins.GetNext(pos)->GetValue();
	double error = target - input;
	m_i += ki * error;
	int d = GetSysTicks() - m_Ticks;
	double dInput = (error - m_LastError) / d;
	double output = kp * error + m_i + kd * dInput;
	pos = m_OutputPins.GetHeadPosition();
	m_OutputPins.GetNext(pos)->SetValue(output);
	m_Ticks = GetSysTicks();
	m_LastError = error;
	return true;
}

void CFXBlockPID::Initialize()
{
	CFXBlock::Initialize();
	m_Ticks = 0;
	m_LastError = 0;
	m_i = 0;
}
