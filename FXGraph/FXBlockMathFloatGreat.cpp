#include "StdAfx.h"
#include "FXBlockMathFloatGreat.h"
IMPLEMENT_SERIAL(CFXBlockMathFloatGreat,CFXBlock,1);

CFXBlockMathFloatGreat::CFXBlockMathFloatGreat(void)
{
}


CFXBlockMathFloatGreat::~CFXBlockMathFloatGreat(void)
{
}


void CFXBlockMathFloatGreat::Create(CFXObject* pBlock)
{
	CFXBlock::Create(pBlock);
	m_Name = "X > Y";
	m_PinInMinCount = 2;
	m_PinInMaxCount = 2;
	m_PinOutMinCount = 1;
	m_PinOutMaxCount = 1;
	m_InputPinTypes.AddTail(Float);
	m_OutputPinTypes.AddTail(Logical);
	AddInputPin(Float,_T("x"));
	AddInputPin(Float,_T("y"));
	AddOutputPin(Logical,_T("z"));
}


bool CFXBlockMathFloatGreat::Calc(void)
{
	if (!CFXBlock::Calc())
		return false;
	POSITION pos = m_InputPins.GetHeadPosition();
	CFXPin* pPin1 = m_InputPins.GetNext(pos);
	CFXPin* pPin2 = m_InputPins.GetNext(pos);
	CFXPin* pPinOut = m_OutputPins.GetHead();
	pPinOut->SetValue( (double)pPin1->GetValue() > (double)pPin2->GetValue() );
	return true;
}
