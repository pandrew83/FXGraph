#include "StdAfx.h"
#include "FXBlockMathIntMod.h"
IMPLEMENT_SERIAL(CFXBlockMathIntMod,CFXBlock,1);

CFXBlockMathIntMod::CFXBlockMathIntMod(void)
{
}

CFXBlockMathIntMod::CFXBlockMathIntMod(CFXBlock *pBlock):CFXBlock(pBlock){
	m_Name = "Mod";
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

bool CFXBlockMathIntMod::Calc(){
	if (!CFXBlock::Calc())
		return false;
	ASSERT(m_InputPins.GetCount() == 2 && m_OutputPins.GetCount() == 1);

	POSITION pos = m_InputPins.GetHeadPosition();
	CFXPin* pPin1 = m_InputPins.GetNext(pos);
	CFXPin* pPin2 = m_InputPins.GetNext(pos);
	CFXPin* pPinOut = m_OutputPins.GetHead();
	pPinOut->SetValue( (int)pPin1->GetValue() % (int)pPin2->GetValue() );
	return true;
}

CFXBlockMathIntMod::~CFXBlockMathIntMod(void)
{
}
