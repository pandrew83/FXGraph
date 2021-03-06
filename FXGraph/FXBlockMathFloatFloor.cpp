﻿#include "StdAfx.h"
#include "FXBlockMathFloatFloor.h"
#include <math.h>
IMPLEMENT_SERIAL(CFXBlockMathFloatFloor,CFXBlock,1);

CFXBlockMathFloatFloor::CFXBlockMathFloatFloor(void)
{
}

void CFXBlockMathFloatFloor::Create(CFXObject* pObject)
{
	CFXBlock::Create(pObject);
	m_Name = "Floor(X)";
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

bool CFXBlockMathFloatFloor::Calc(){
	if (!CFXBlock::Calc())
		return false;
	double x = m_InputPins.GetHead()->GetValue();
	m_OutputPins.GetHead()->SetValue( floor(x) );
	return true;
}

CFXBlockMathFloatFloor::~CFXBlockMathFloatFloor(void)
{
}
