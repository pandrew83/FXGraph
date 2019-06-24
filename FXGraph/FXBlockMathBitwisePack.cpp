#include "StdAfx.h"
#include "FXBlockMathBitwisePack.h"

IMPLEMENT_SERIAL(CFXBlockMathBitwisePack,CFXBlock,1);


CFXBlockMathBitwisePack::CFXBlockMathBitwisePack(void)
{
}

void CFXBlockMathBitwisePack::Create(CFXObject* pObject)
{
	CFXBlock::Create(pObject);
	m_Name = "Bit Pack";
	m_InputPinTypes.AddTail(Logical);
	m_OutputPinTypes.AddTail(Int);
	m_PinInMinCount = 1;
	m_PinInMaxCount = 32;
	m_PinOutMinCount = 1;
	m_PinOutMaxCount = 1;
	AddInputPin(Logical,_T("x"));
	AddInputPin(Logical,_T("y"));
	AddOutputPin(Int,_T("z"),true,true,false,CFXPin::UNSIGNED);
}

CFXBlockMathBitwisePack::~CFXBlockMathBitwisePack(void)
{
}


bool CFXBlockMathBitwisePack::Calc(void)
{
	if (!CFXBlock::Calc())
		return false;
	int value = 0;
	int k = 1;
	POSITION pos = m_InputPins.GetHeadPosition();
	while (pos){
		CFXPin* pPin = m_InputPins.GetNext(pos);
		if ((bool)pPin->GetValue())
			value = value | k;
		k = k << 1;
	}
	m_OutputPins.GetHead()->SetValue( value );
	return true;
}
