﻿#include "StdAfx.h"
#include "FXBlockMathFloatEqual.h"
IMPLEMENT_SERIAL(CFXBlockMathFloatEqual,CFXBlock,1);

CFXBlockMathFloatEqual::CFXBlockMathFloatEqual(void)
{
}

void CFXBlockMathFloatEqual::Create(CFXObject* pObject)
{
	CFXBlock::Create(pObject);
	m_Name = "X = Y";
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

CFXBlockMathFloatEqual::~CFXBlockMathFloatEqual(void)
{
}


bool CFXBlockMathFloatEqual::Calc(void)
{
	if (!CFXBlock::Calc())
		return false;
	POSITION pos = m_InputPins.GetHeadPosition();
	CFXPin* pPin1 = m_InputPins.GetNext(pos);
	CFXPin* pPin2 = m_InputPins.GetNext(pos);
	CFXPin* pPinOut = m_OutputPins.GetHead();
	pPinOut->SetValue( (double)pPin1->GetValue() == (double)pPin2->GetValue() );
	return true;
}
