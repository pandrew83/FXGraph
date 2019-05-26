#include "StdAfx.h"
#include "FXBlockComparatorUp.h"

IMPLEMENT_SERIAL(CFXBlockComparatorUp,CFXBlock,1);

CFXBlockComparatorUp::CFXBlockComparatorUp(void)
	: m_Prev(false)
{
}
CFXBlockComparatorUp::CFXBlockComparatorUp(CFXBlock* pBlock): CFXBlock(pBlock){
	m_Prev = false;
	m_Name = "Comp Up";
	m_InputPinTypes.AddTail(Float);
	m_OutputPinTypes.AddTail(Logical);
	m_PinInMinCount = 3;
	m_PinInMaxCount = 3;
	m_PinOutMinCount = 1;
	m_PinOutMaxCount = 1;
	AddInputPin(Float,_T("x"));
	AddInputPin(Float,_T("x_hi"));
	AddInputPin(Float,_T("hys"));
	AddOutputPin(Logical,_T("z"));
}

bool CFXBlockComparatorUp::Calc(){
	if (!CFXBlock::Calc())
		return false;
	POSITION pos = m_InputPins.GetHeadPosition();
	double x = (double)m_InputPins.GetNext(pos)->GetValue();
	double x_hi = (double)m_InputPins.GetNext(pos)->GetValue();
	double hys = (double)m_InputPins.GetNext(pos)->GetValue();
	bool z = false;
	if (x > x_hi)
		z = true;
	else 
		if (x < x_hi - hys)
			z = false;
		else
			z = m_Prev;
	m_Prev = z;
	CFXPin* pPin = m_OutputPins.GetHead();
	pPin->SetValue(z);
	return true;
}


CFXBlockComparatorUp::~CFXBlockComparatorUp(void)
{
}


void CFXBlockComparatorUp::Initialize(void)
{
	CFXBlock::Initialize();
}
