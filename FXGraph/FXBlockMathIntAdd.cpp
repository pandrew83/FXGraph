#include "StdAfx.h"
#include "FXBlockMathIntAdd.h"
IMPLEMENT_SERIAL(CFXBlockMathIntAdd,CFXBlock,1);


CFXBlockMathIntAdd::CFXBlockMathIntAdd(void)
{
}


CFXBlockMathIntAdd::~CFXBlockMathIntAdd(void)
{
}

CFXBlockMathIntAdd::CFXBlockMathIntAdd(CFXBlock* pBlock):CFXBlock(pBlock){
	m_Name = "X + Y";
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

bool CFXBlockMathIntAdd::Calc(void)
{
	if (!CFXBlock::Calc())
		return false;
	ASSERT(m_InputPins.GetCount() >= 2 && m_OutputPins.GetCount() == 1);

	int v = 0;
	POSITION pos = m_InputPins.GetHeadPosition();
	while (pos){
		CFXPin* pPin = m_InputPins.GetNext(pos);
		v = v + (int)pPin->GetValue();
	}
	CFXPin* pPinOut = m_OutputPins.GetHead();
	pPinOut->SetValue(v);
	return true;
}
