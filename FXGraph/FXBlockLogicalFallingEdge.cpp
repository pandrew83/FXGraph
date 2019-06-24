#include "StdAfx.h"
#include "FXBlockLogicalFallingEdge.h"

IMPLEMENT_SERIAL(CFXBlockLogicalFallingEdge,CFXBlock,1);

CFXBlockLogicalFallingEdge::CFXBlockLogicalFallingEdge(void)
{
}

void CFXBlockLogicalFallingEdge::Create(CFXObject* pBlock)
{
	CFXBlock::Create(pBlock);
	m_Prev = false;
	m_MinHeight = m_Height = 50;
	m_Name = "Fall Edge";
	m_InputPinTypes.AddTail(Logical);
	m_OutputPinTypes.AddTail(Logical);
	m_PinInMinCount = 1;
	m_PinInMaxCount = 1;
	m_PinOutMinCount = 1;
	m_PinOutMaxCount = 1;
	AddInputPin(Logical,_T("x"));
	AddOutputPin(Logical,_T("z"));
}

bool CFXBlockLogicalFallingEdge::Calc(){
	if (!CFXBlock::Calc())
		return false;
	bool x = (bool)m_InputPins.GetHead()->GetValue();
	bool z = false;
	if (m_Prev && !x)
		z = true;
	m_Prev = x;
	m_OutputPins.GetHead()->SetValue(z);
	return true;
}

CFXBlockLogicalFallingEdge::~CFXBlockLogicalFallingEdge(void)
{
}


void CFXBlockLogicalFallingEdge::Initialize(void)
{
	CFXBlock::Initialize();
	m_Prev = false;
}
