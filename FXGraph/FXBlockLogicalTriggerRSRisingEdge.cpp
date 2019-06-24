#include "StdAfx.h"
#include "FXBlockLogicalTriggerRSRisingEdge.h"
IMPLEMENT_SERIAL(CFXBlockLogicalTriggerRSRisingEdge,CFXBlock,1);

CFXBlockLogicalTriggerRSRisingEdge::CFXBlockLogicalTriggerRSRisingEdge(void)
{
}

void CFXBlockLogicalTriggerRSRisingEdge::Create(CFXObject* pObject)
{
	CFXBlock::Create(pObject);
	m_PrevR = false;
	m_PrevS = false;
	m_PrevZ = false;
	m_Name = "Trig RS RE";
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

bool CFXBlockLogicalTriggerRSRisingEdge::Calc(){
	if (!CFXBlock::Calc())
		return false;
	POSITION pos = m_InputPins.GetHeadPosition();
	bool r = m_InputPins.GetNext(pos)->GetValue();
	bool s = m_InputPins.GetNext(pos)->GetValue();
	bool z = false;
	CFXPin* pPin_z = m_OutputPins.GetHead();
	if (!m_PrevS && s && !m_PrevR && !r){
		z = true;
	}
	if (!m_PrevR && r){
		z = false;
	}
	m_PrevZ = z;
	m_PrevR = r;
	m_PrevS = s;
	pPin_z->SetValue(z);
	return true;
}

CFXBlockLogicalTriggerRSRisingEdge::~CFXBlockLogicalTriggerRSRisingEdge(void)
{
}


void CFXBlockLogicalTriggerRSRisingEdge::Initialize(void)
{
	CFXBlock::Initialize();
	m_PrevR = false;
	m_PrevS = false;
	m_PrevZ = false;
}
