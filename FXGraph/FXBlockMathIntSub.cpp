#include "StdAfx.h"
#include "FXBlockMathIntSub.h"
IMPLEMENT_SERIAL(CFXBlockMathIntSub,CFXBlock,1);


CFXBlockMathIntSub::CFXBlockMathIntSub(void)
{
}

CFXBlockMathIntSub::CFXBlockMathIntSub(CFXBlock* pBlock):CFXBlock(pBlock){
	m_Name = "Sub";
	m_PinInMinCount = 2;
	m_PinInMaxCount = 32;
	m_PinOutMinCount = 1;
	m_PinOutMaxCount = 1;
	m_InputPinTypes.AddTail(Int);
	m_OutputPinTypes.AddTail(Int);
	AddInputPin(Int,_T("x"));
	AddInputPin(Int,_T("y"));
	AddOutputPin(Int,_T("z"));
}

CFXBlockMathIntSub::~CFXBlockMathIntSub(void)
{
}


bool CFXBlockMathIntSub::Calc(void)
{
	if (!CFXBlock::Calc())
		return false;
	ASSERT(m_InputPins.GetCount() == 2 && m_OutputPins.GetCount() == 1);

	POSITION pos = m_InputPins.GetHeadPosition();
	CFXPin* pPin1 = m_InputPins.GetNext(pos);
	CFXPin* pPin2 = m_InputPins.GetNext(pos);
	CFXPin* pPinOut = m_OutputPins.GetHead();
	pPinOut->SetValue((int)pPin1->GetValue() * (int)pPin2->GetValue());
	return true;
}
