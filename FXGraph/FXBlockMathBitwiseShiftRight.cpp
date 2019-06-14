#include "StdAfx.h"
#include "FXBlockMathBitwiseShiftRight.h"

IMPLEMENT_SERIAL(CFXBlockMathBitwiseShiftRight,CFXBlock,1);

CFXBlockMathBitwiseShiftRight::CFXBlockMathBitwiseShiftRight(void)
{
}

CFXBlockMathBitwiseShiftRight::CFXBlockMathBitwiseShiftRight(CFXBlock* pBlock):CFXBlock(pBlock){
	m_Name = "Shift Right";
	m_InputPinTypes.AddTail(Int);
	m_OutputPinTypes.AddTail(Int);
	m_PinInMinCount = 2;
	m_PinInMaxCount = 2;
	m_PinOutMinCount = 1;
	m_PinOutMaxCount = 1;
	AddInputPin(Int,_T("x"),true,true,false,CFXPin::UNSIGNED);
	AddInputPin(Int,_T("k"),true,true,false,CFXPin::UNSIGNED);
	AddOutputPin(Int,_T("z"),true,true,false,CFXPin::UNSIGNED);
}

CFXBlockMathBitwiseShiftRight::~CFXBlockMathBitwiseShiftRight(void)
{
}


bool CFXBlockMathBitwiseShiftRight::Calc(void)
{
	// Должно быть только два пина
	ASSERT(m_InputPins.GetCount() == 2);
	if (!CFXBlock::Calc())
		return false;
	POSITION pos = m_InputPins.GetHeadPosition();
	CFXPin* pPinV = m_InputPins.GetNext(pos);
	CFXPin* pPinK = m_InputPins.GetNext(pos);

	int v = (int)pPinV->GetValue() >> (int)pPinK->GetValue();
	m_OutputPins.GetHead()->SetValue( v );
	return true;
}
