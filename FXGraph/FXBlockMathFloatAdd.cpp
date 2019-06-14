#include "StdAfx.h"
#include "FXBlockMathFloatAdd.h"

IMPLEMENT_SERIAL(CFXBlockMathFloatAdd,CFXBlock,1);

CFXBlockMathFloatAdd::CFXBlockMathFloatAdd(void)
{
}


CFXBlockMathFloatAdd::~CFXBlockMathFloatAdd(void)
{
}

CFXBlockMathFloatAdd::CFXBlockMathFloatAdd(CFXBlock* pBlock) :CFXBlock(pBlock) {
	m_Name = "X + Y";
	m_PinInMaxCount = 32;
	m_PinInMinCount = 2;
	m_PinOutMinCount = 1;
	m_PinOutMaxCount = 1;
	m_InputPinTypes.AddTail(Float);
	m_OutputPinTypes.AddTail(Float);
	AddInputPin(Float, _T("x"));
	AddInputPin(Float, _T("y"));
	AddOutputPin(Float, _T("z"));
}

bool CFXBlockMathFloatAdd::Calc(void)
{
	ASSERT(m_InputPins.GetCount() > 1 && m_OutputPins.GetCount() == 1);
	if (!CFXBlock::Calc())
		return false;
	double v = 0;
	POSITION pos = m_InputPins.GetHeadPosition();
	while (pos){
		CFXPin* pPin = m_InputPins.GetNext(pos);
		v = v + (double)pPin->GetValue();
	}
	CFXPin* pPinOut = m_OutputPins.GetHead();
	pPinOut->SetValue(v);
	return true;
}
