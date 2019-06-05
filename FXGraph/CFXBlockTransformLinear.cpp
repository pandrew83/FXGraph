#include "stdafx.h"
#include "CFXBlockTransformLinear.h"
IMPLEMENT_SERIAL(CFXBlockTransformLinear, CFXBlock, 1);

CFXBlockTransformLinear::CFXBlockTransformLinear()
{
}

CFXBlockTransformLinear::CFXBlockTransformLinear(CFXBlock* pBlock) : CFXBlock(pBlock)
{
	m_Name = "Transform Linear";
	m_MinHeight = m_Height = 175;
	m_PinInMaxCount = 5;
	m_PinInMinCount = 5;
	m_PinOutMinCount = 1;
	m_PinOutMaxCount = 1;
	m_InputPinTypes.AddTail(Float);
	m_OutputPinTypes.AddTail(Float);
	AddInputPin(Float, _T("x"));
	AddInputPin(Float, _T("x_min"));
	AddInputPin(Float, _T("x_max"));
	AddInputPin(Float, _T("y_min"));
	AddInputPin(Float, _T("y_max"));
	AddOutputPin(Float, _T("z"));
}

bool CFXBlockTransformLinear::Calc()
{
	if (!CFXBlock::Calc())
		return false;
	POSITION pos = m_InputPins.GetHeadPosition();
	double x = m_InputPins.GetNext(pos)->GetValue();
	double x_min = m_InputPins.GetNext(pos)->GetValue();
	double x_max = m_InputPins.GetNext(pos)->GetValue();
	double y_min = m_InputPins.GetNext(pos)->GetValue();
	double y_max = m_InputPins.GetNext(pos)->GetValue();

	double y = y_min + (x - x_min) * (y_max - y_min) / (x_max - x_min);
	m_OutputPins.GetHead()->SetValue(y);
	return true;
}
