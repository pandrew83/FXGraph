#include "StdAfx.h"
#include "FXBlockLogicalAnd.h"
#include "FXBlock.h"

IMPLEMENT_SERIAL( CFXBlockLogicalAnd, CFXBlock, 1 );


CFXBlockLogicalAnd::CFXBlockLogicalAnd(void) : CFXBlock()
{
}

void CFXBlockLogicalAnd::Create(CFXObject* pBlock){
	CFXBlock::Create(pBlock);
	m_bCalc = true;
	m_Name = "And";
	m_PinInMinCount = 2;
	m_PinInMaxCount = 32;
	m_PinOutMinCount = 1;
	m_PinOutMaxCount = 1;
	m_InputPinTypes.AddTail(Logical);
	m_OutputPinTypes.AddTail(Logical);

	AddInputPin(Logical,_T("x"));
	AddInputPin(Logical,_T("y"));
	AddOutputPin(Logical,_T("z"));
}


CFXBlockLogicalAnd::~CFXBlockLogicalAnd(void)
{
}


bool CFXBlockLogicalAnd::Calc(void)
{
	if (!CFXBlock::Calc())
		return false;
	bool value = true;
	POSITION pos = m_InputPins.GetHeadPosition();
	while (pos){
		CFXPin* pPin = m_InputPins.GetNext(pos);
		value = value && (bool)pPin->GetValue();
	}
	m_OutputPins.GetHead()->SetValue( value );
	return true;
}
