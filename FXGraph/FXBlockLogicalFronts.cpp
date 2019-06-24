#include "StdAfx.h"
#include "FXBlockLogicalFronts.h"
IMPLEMENT_SERIAL(CFXBlockLogicalFronts,CFXBlock,1);

CFXBlockLogicalFronts::CFXBlockLogicalFronts(void)
{
}

void CFXBlockLogicalFronts::Create(CFXObject* pObject)
{
	CFXBlock::Create(pObject);
	m_Prev = false;
	m_Name = "Fronts";
	m_InputPinTypes.AddTail(Logical);
	m_OutputPinTypes.AddTail(Logical);
	m_PinInMinCount = 1;
	m_PinInMaxCount = 1;
	m_PinOutMinCount = 2;
	m_PinOutMaxCount = 2;
	AddInputPin(Logical,_T("X"));
	AddOutputPin(Logical,_T("Raise"));
	AddOutputPin(Logical,_T("Fall"));
}

bool CFXBlockLogicalFronts::Calc(){
	if (!CFXBlock::Calc())
		return false;
	bool x = m_InputPins.GetHead()->GetValue();
	bool r = false;
	bool f = false;
	if (!m_Prev && x)
		r = true;
	if (m_Prev && !x)
		f = true;
	m_Prev = x;
	POSITION pos = m_OutputPins.GetHeadPosition();
	CFXPin* pPinR = m_OutputPins.GetNext(pos);
	CFXPin* pPinF = m_OutputPins.GetNext(pos);
	pPinR->SetValue(r);
	pPinF->SetValue(f);
	return true;
}

CFXBlockLogicalFronts::~CFXBlockLogicalFronts(void)
{
}


void CFXBlockLogicalFronts::Initialize(void)
{
	CFXBlock::Initialize();
	m_Prev = false;
}
