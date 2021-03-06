﻿#include "StdAfx.h"
#include "FXBlockMathCos.h"
#include <math.h>
IMPLEMENT_SERIAL(CFXBlockMathCos,CFXBlock,1);

CFXBlockMathCos::CFXBlockMathCos(void)
{
}

void CFXBlockMathCos::Create(CFXObject* pObject)
{
	CFXBlock::Create(pObject);
	m_Name = "Cos(X)";
	m_MinHeight = m_Height = 50;
	m_PinInMaxCount = 1;
	m_PinInMinCount = 1;
	m_PinOutMinCount = 1;
	m_PinOutMaxCount = 1;
	m_InputPinTypes.AddTail(Float);
	m_OutputPinTypes.AddTail(Float);
	AddInputPin(Float,_T("x"));
	AddOutputPin(Float,_T("z"));
}

bool CFXBlockMathCos::Calc(){
	if (!CFXBlock::Calc())
		return false;
	double x = m_InputPins.GetHead()->GetValue();
	m_OutputPins.GetHead()->SetValue( cos(x) );
	return true;
}

CFXBlockMathCos::~CFXBlockMathCos(void)
{
}
