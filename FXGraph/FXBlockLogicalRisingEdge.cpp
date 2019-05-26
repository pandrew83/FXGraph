#include "StdAfx.h"
#include "FXBlockLogicalRisingEdge.h"

IMPLEMENT_SERIAL(CFXBlockLogicalRisingEdge,CFXBlock,1);

CFXBlockLogicalRisingEdge::CFXBlockLogicalRisingEdge(void)
{
}

CFXBlockLogicalRisingEdge::CFXBlockLogicalRisingEdge(CFXBlock* pBlock):CFXBlock(pBlock){
	m_Prev = false;
	m_Name = "Raise Edge";
	m_InputPinTypes.AddTail(Logical);
	m_OutputPinTypes.AddTail(Logical);
	m_PinInMinCount = 1;
	m_PinInMaxCount = 1;
	m_PinOutMinCount = 1;
	m_PinOutMaxCount = 1;
	AddInputPin(Logical,_T("x"));
	AddOutputPin(Logical,_T("z"));
}

bool CFXBlockLogicalRisingEdge::Calc(){
	if (!CFXBlock::Calc())
		return false;
	bool x = (bool)m_InputPins.GetHead()->GetValue();
	bool z = false;
	if (!m_Prev && x)
		z = true;
	m_Prev = x;
	m_OutputPins.GetHead()->SetValue(z);
	return true;
}

CFXBlockLogicalRisingEdge::~CFXBlockLogicalRisingEdge(void)
{
}


void CFXBlockLogicalRisingEdge::Initialize(void)
{
	CFXBlock::Initialize();
	m_Prev = false;
}
