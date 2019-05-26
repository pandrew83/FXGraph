#include "StdAfx.h"
#include "FXBlockMathFloatSub.h"
IMPLEMENT_SERIAL(CFXBlockMathFloatSub,CFXBlock,1);


CFXBlockMathFloatSub::CFXBlockMathFloatSub(void)
{
}


CFXBlockMathFloatSub::~CFXBlockMathFloatSub(void)
{
}


bool CFXBlockMathFloatSub::Calc(void)
{
	if (!CFXBlock::Calc())
		return false;
	ASSERT(m_InputPins.GetCount() == 2 && m_OutputPins.GetCount() == 1);

	POSITION pos = m_InputPins.GetHeadPosition();
	CFXPin* pPin1 = m_InputPins.GetNext(pos);
	CFXPin* pPin2 = m_InputPins.GetNext(pos);
	CFXPin* pPinOut = m_OutputPins.GetHead();
	pPinOut->SetValue( (double)pPin1->GetValue() - (double)pPin2->GetValue() );
	return true;
}
