#include "StdAfx.h"
#include "FXBlockLogicalNot.h"
IMPLEMENT_SERIAL(CFXBlockLogicalNot,CFXBlock,1);

CFXBlockLogicalNot::CFXBlockLogicalNot(CFXBlock* pBlock):CFXBlock(pBlock){
	m_Name = "Not";
	m_MinHeight = m_Height = 50; 
	m_PinInMinCount = 1;
	m_PinInMaxCount = 1;
	m_PinOutMinCount = 1;
	m_PinOutMaxCount = 1;
	m_InputPinTypes.AddTail(Logical);
	m_OutputPinTypes.AddTail(Logical);

	AddInputPin(Logical,_T("x"));
	AddOutputPin(Logical,_T("z"));
}

CFXBlockLogicalNot::CFXBlockLogicalNot(void)
{
}


CFXBlockLogicalNot::~CFXBlockLogicalNot(void)
{
}


bool CFXBlockLogicalNot::Calc(void)
{
	if (!CFXBlock::Calc())
		return false;
	CFXPin* pPinIn = m_InputPins.GetHead();
	CFXPin* pPinOut = m_OutputPins.GetHead();
	pPinOut->SetValue( !(bool)pPinIn->GetValue() );
	return true;
}
