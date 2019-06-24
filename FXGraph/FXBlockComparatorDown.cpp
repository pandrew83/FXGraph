#include "StdAfx.h"
#include "FXBlockComparatorDown.h"

IMPLEMENT_SERIAL(CFXBlockComparatorDown,CFXBlock,1);

CFXBlockComparatorDown::CFXBlockComparatorDown(void)
	: m_Prev(false)
{
}

void CFXBlockComparatorDown::Create(CFXObject* pBlock)
{
	CFXBlock::Create(pBlock);
	m_Prev = false;
	m_Name = "Comp Down";
	m_InputPinTypes.AddTail(Float);
	m_OutputPinTypes.AddTail(Logical);
	m_PinInMinCount = 3;
	m_PinInMaxCount = 3;
	m_PinOutMinCount = 1;
	m_PinOutMaxCount = 1;
	AddInputPin(Float,_T("x"));
	AddInputPin(Float,_T("x_low"));
	AddInputPin(Float,_T("hys"));
	AddOutputPin(Logical,_T("z"));
}

bool CFXBlockComparatorDown::Calc(){
	if (!CFXBlock::Calc())
		return false;
	POSITION pos = m_InputPins.GetHeadPosition();
	double x = (double)m_InputPins.GetNext(pos)->GetValue();
	double x_low = (double)m_InputPins.GetNext(pos)->GetValue();
	double hys = (double)m_InputPins.GetNext(pos)->GetValue();
	bool z = 0;
	if (x < x_low)
		z = true;
	else 
		if (x > x_low + hys)
			z = false;
		else
			z = m_Prev;
	m_Prev = z;
	CFXPin* pPin = m_OutputPins.GetHead();
	pPin->SetValue(z);
	return true;
}

CFXBlockComparatorDown::~CFXBlockComparatorDown(void)
{
}


void CFXBlockComparatorDown::Initialize(void)
{
	CFXBlock::Initialize();
	m_Prev = false;
}
