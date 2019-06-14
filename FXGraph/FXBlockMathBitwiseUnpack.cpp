#include "StdAfx.h"
#include "FXBlockMathBitwiseUnpack.h"
IMPLEMENT_SERIAL(CFXBlockMathBitwiseUnpack,CFXBlock,1);

CFXBlockMathBitwiseUnpack::CFXBlockMathBitwiseUnpack(void)
{
}

CFXBlockMathBitwiseUnpack::CFXBlockMathBitwiseUnpack(CFXBlock* pBlock) : CFXBlock(pBlock){
	m_Name = "Bit Unpack";
	m_InputPinTypes.AddTail(Int);
	m_OutputPinTypes.AddTail(Logical);
	m_PinInMinCount = 1;
	m_PinInMaxCount = 1;
	m_PinOutMinCount = 1;
	m_PinOutMaxCount = 32;
	AddInputPin(Int,_T("x"),true,true,false,CFXPin::UNSIGNED);
	AddOutputPin(Logical,_T("z1"));
	AddOutputPin(Logical,_T("z2"));
}

CFXBlockMathBitwiseUnpack::~CFXBlockMathBitwiseUnpack(void)
{
}


bool CFXBlockMathBitwiseUnpack::Calc(void)
{
	// Должно быть только два пина
	ASSERT(m_InputPins.GetCount() == 1);
	if (!CFXBlock::Calc())
		return false;
	int v = (int)m_InputPins.GetHead()->GetValue();
	int k = 1;

	POSITION pos = m_OutputPins.GetHeadPosition();
	while (pos){
		CFXPin* pPin = m_OutputPins.GetNext(pos);
		if (v & k)
			pPin->SetValue( true );
		else
			pPin->SetValue( false );
		k = k << 1;
	}
	return true;
}
