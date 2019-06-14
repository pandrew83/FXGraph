#include "StdAfx.h"
#include "FXBlockLogicalXor.h"
IMPLEMENT_SERIAL(CFXBlockLogicalXor,CFXBlock,1);


CFXBlockLogicalXor::CFXBlockLogicalXor(void)
{
}

CFXBlockLogicalXor::CFXBlockLogicalXor(CFXBlock* pBlock):CFXBlock(pBlock){
	m_Name = "Xor";
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

CFXBlockLogicalXor::~CFXBlockLogicalXor(void)
{
}


bool CFXBlockLogicalXor::Calc(void)
{
	if (!CFXBlock::Calc())
		return false;
	bool value = false;
	POSITION pos = m_InputPins.GetHeadPosition();
	while (pos){
		CFXPin* pPin = m_InputPins.GetNext(pos);
		value = value != (bool)pPin->GetValue();
	}
	m_OutputPins.GetHead()->SetValue( value );
	return true;
}
