#include "StdAfx.h"
#include "FXBlockMathFloatLess.h"
IMPLEMENT_SERIAL(CFXBlockMathFloatLess,CFXBlock,1);


CFXBlockMathFloatLess::CFXBlockMathFloatLess(void)
{
}

CFXBlockMathFloatLess::CFXBlockMathFloatLess(CFXBlock* pBlock) : CFXBlock(pBlock){
	m_Name = "X < Y";
	m_PinInMinCount = 2;
	m_PinInMaxCount = 2;
	m_PinOutMinCount = 1;
	m_PinOutMaxCount = 1;
	m_InputPinTypes.AddTail(Float);
	m_OutputPinTypes.AddTail(Logical);
	AddInputPin(Float,_T("x"));
	AddInputPin(Float,_T("y"));
	AddOutputPin(Logical,_T("z"));
}

CFXBlockMathFloatLess::~CFXBlockMathFloatLess(void)
{
}


bool CFXBlockMathFloatLess::Calc(void)
{
	if (!CFXBlock::Calc())
		return false;
	POSITION pos = m_InputPins.GetHeadPosition();
	CFXPin* pPin1 = m_InputPins.GetNext(pos);
	CFXPin* pPin2 = m_InputPins.GetNext(pos);
	CFXPin* pPinOut = m_OutputPins.GetHead();
	pPinOut->SetValue( (double)pPin1->GetValue() < (double)pPin2->GetValue() );
	return true;
}
