#include "StdAfx.h"
#include "FXBlockBitwiseAnd.h"


CFXBlockMathBitwiseAnd::CFXBlockMathBitwiseAnd(void){
}

void CFXBlockMathBitwiseAnd::Create(CFXObject* pBlock)
{
	CFXBlock::Create(pBlock);
	m_Name = "Bit And";
	m_InputPinTypes.AddTail(Int);
	m_OutputPinTypes.AddTail(Int);
	m_PinInMinCount = 2;
	m_PinInMaxCount = 32;
	m_PinOutMinCount = 1;
	m_PinOutMaxCount = 1;
	AddInputPin(Int,_T("x"),true,true,false,CFXPin::UNSIGNED);
	AddInputPin(Int,_T("y"),true,true,false,CFXPin::UNSIGNED);
	AddOutputPin(Int,_T("z"),true,true,false,CFXPin::UNSIGNED);
}

CFXBlockMathBitwiseAnd::~CFXBlockMathBitwiseAnd(void)
{
}


bool CFXBlockMathBitwiseAnd::Calc(void)
{
	if (!CFXBlock::Calc())
		return false;
	int value = 0xffffffff;
	POSITION pos = m_InputPins.GetHeadPosition();
	while (pos){
		CFXPin* pPin = m_InputPins.GetNext(pos);
		value = value & (int)pPin->GetValue();
	}
	m_OutputPins.GetHead()->SetValue( value );
	return true;
}
