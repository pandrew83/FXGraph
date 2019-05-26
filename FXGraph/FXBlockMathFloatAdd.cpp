#include "StdAfx.h"
#include "FXBlockMathFloatAdd.h"

IMPLEMENT_SERIAL(CFXBlockMathFloatAdd,CFXBlock,1);

CFXBlockMathFloatAdd::CFXBlockMathFloatAdd(void)
{
}


CFXBlockMathFloatAdd::~CFXBlockMathFloatAdd(void)
{
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
