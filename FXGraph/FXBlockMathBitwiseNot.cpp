#include "StdAfx.h"
#include "FXBlockMathBitwiseNot.h"

IMPLEMENT_SERIAL(CFXBlockMathBitwiseNot,CFXBlock,1);

CFXBlockMathBitwiseNot::CFXBlockMathBitwiseNot(void)
{
}

CFXBlockMathBitwiseNot::CFXBlockMathBitwiseNot(CFXBlock* pBlock) : CFXBlock(pBlock){
	m_Name = "Bit Not";
	m_MinHeight = m_Height = 50;
	m_InputPinTypes.AddTail(Int);
	m_OutputPinTypes.AddTail(Int);
	m_PinInMinCount = 1;
	m_PinInMaxCount = 1;
	m_PinOutMinCount = 1;
	m_PinOutMaxCount = 1;
	AddInputPin(Int,_T("x"),true,true,false,CFXPin::UNSIGNED);
	AddOutputPin(Int,_T("z"),true,true,false,CFXPin::UNSIGNED);
}

CFXBlockMathBitwiseNot::~CFXBlockMathBitwiseNot(void)
{
}


bool CFXBlockMathBitwiseNot::Calc(void)
{
	if (!CFXBlock::Calc())
		return false;
	int value = (int)m_InputPins.GetHead()->GetValue();
	m_OutputPins.GetHead()->SetValue( ~value );
	return true;
}
