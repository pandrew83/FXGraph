#include "StdAfx.h"
#include "FXBlockMathBitwiseXor.h"

IMPLEMENT_SERIAL(CFXBlockMathBitwiseXor,CFXBlock,1);

CFXBlockMathBitwiseXor::CFXBlockMathBitwiseXor(void)
{
}

void CFXBlockMathBitwiseXor::Create(CFXObject* pObject)
{
	CFXBlock::Create(pObject);
	m_Name = "Bit Xor";
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

CFXBlockMathBitwiseXor::~CFXBlockMathBitwiseXor(void)
{
}


bool CFXBlockMathBitwiseXor::Calc(void)
{
	ASSERT(m_OutputPins.GetCount() == 1);
	if (!CFXBlock::Calc())
		return false;

	int v = 0;
	POSITION pos = m_InputPins.GetHeadPosition();
	while (pos){
		CFXPin* pPin = m_OutputPins.GetNext(pos);
		v = v ^ (int)pPin->GetValue();
	}
	m_OutputPins.GetHead()->SetValue( v );
	return true;
}
