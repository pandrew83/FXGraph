#include "StdAfx.h"
#include "FXBlockLogicalTriggerRS.h"
IMPLEMENT_SERIAL(CFXBlockLogicalTriggerRS,CFXBlock,1);

CFXBlockLogicalTriggerRS::CFXBlockLogicalTriggerRS(void)
{
}

CFXBlockLogicalTriggerRS::CFXBlockLogicalTriggerRS(CFXBlock* pBlock):CFXBlock(pBlock){
	m_Prev = false;
	m_Name = "Trig RS";
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

bool CFXBlockLogicalTriggerRS::Calc(){
	if (!CFXBlock::Calc())
		return false;
	POSITION pos = m_InputPins.GetHeadPosition();
	bool r = m_InputPins.GetNext(pos)->GetValue();
	bool s = m_InputPins.GetNext(pos)->GetValue();
	bool z = false;
	CFXPin* pPin_z = m_OutputPins.GetHead();
	if (r)
		z = false;
	else
		if (s && !r)
			z = true;
		else
			z = m_Prev;
	m_Prev = z;
	pPin_z->SetValue(z);
	return true;
}

CFXBlockLogicalTriggerRS::~CFXBlockLogicalTriggerRS(void)
{
}


void CFXBlockLogicalTriggerRS::Initialize(void)
{
	CFXBlock::Initialize();
	m_Prev = false;
}
