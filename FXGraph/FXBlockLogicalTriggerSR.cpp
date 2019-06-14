#include "StdAfx.h"
#include "FXBlockLogicalTriggerSR.h"
IMPLEMENT_SERIAL(CFXBlockLogicalTriggerSR,CFXBlock,1);

CFXBlockLogicalTriggerSR::CFXBlockLogicalTriggerSR(void)
{
}

CFXBlockLogicalTriggerSR::CFXBlockLogicalTriggerSR(CFXBlock* pBlock):CFXBlock(pBlock){
	m_Prev = false;
	m_Name = "Trig SR";
	m_InputPinTypes.AddTail(Logical);
	m_OutputPinTypes.AddTail(Logical);
	m_PinInMinCount = 2;
	m_PinInMaxCount = 2;
	m_PinOutMinCount = 1;
	m_PinOutMaxCount = 1;
	AddInputPin(Logical,_T("R"));
	AddInputPin(Logical,_T("S"));
	AddOutputPin(Logical,_T("Z"));
}

bool CFXBlockLogicalTriggerSR::Calc(){
	if (!CFXBlock::Calc())
		return false;
	POSITION pos = m_InputPins.GetHeadPosition();
	bool r = m_InputPins.GetNext(pos)->GetValue();
	bool s = m_InputPins.GetNext(pos)->GetValue();
	bool z = false;
	CFXPin* pPin_z = m_OutputPins.GetHead();
	if (s)
		z = true;
	else
		if (!s && r)
			z = false;
		else
			z = m_Prev;
	m_Prev = z;
	pPin_z->SetValue(z);
	return true;
}

CFXBlockLogicalTriggerSR::~CFXBlockLogicalTriggerSR(void)
{
}


void CFXBlockLogicalTriggerSR::Initialize(void)
{
	CFXBlock::Initialize();
	m_Prev = false;
}
