#include "StdAfx.h"
#include "FXBlockMathIntDiv.h"
IMPLEMENT_SERIAL(CFXBlockMathIntDiv,CFXBlock,1);


CFXBlockMathIntDiv::CFXBlockMathIntDiv(void)
{
}


CFXBlockMathIntDiv::~CFXBlockMathIntDiv(void)
{
}


bool CFXBlockMathIntDiv::Calc(void)
{
	if (!CFXBlock::Calc())
		return false;
	ASSERT(m_InputPins.GetCount() == 2 && m_OutputPins.GetCount() == 1);

	POSITION pos = m_InputPins.GetHeadPosition();
	CFXPin* pPin1 = m_InputPins.GetNext(pos);
	CFXPin* pPin2 = m_InputPins.GetNext(pos);
	CFXPin* pPinOut = m_OutputPins.GetHead();
	pPinOut->SetValue( (int)pPin1->GetValue() / (int)pPin2->GetValue() );
	return true;
}
