#include "StdAfx.h"
#include "FXBlockExtensionA01.h"
#include "FXBlockExtension.h"

IMPLEMENT_SERIAL(CFXBlockExtensionA01,CFXBlockExtension,1);

CFXBlockExtensionA01::CFXBlockExtensionA01(void)
{
}


CFXBlockExtensionA01::~CFXBlockExtensionA01(void)
{
}


void CFXBlockExtensionA01::Create(CFXObject* pBlock)
{
	CFXBlock::Create(pBlock);
	m_Name = _T("NiMod-A01");
	m_MinHeight = 300;
	m_Height = 300;
	m_PinInMinCount = 0;
	m_PinInMaxCount = 0;
	m_PinOutMinCount = 10;
	m_PinOutMaxCount = 10;
	m_OutputPinTypes.AddTail(Float);
	AddOutputPin(Float,_T("AI.01"));
	AddOutputPin(Float,_T("AI.02"));
	AddOutputPin(Float,_T("AI.03"));
	AddOutputPin(Float,_T("AI.04"));
	AddOutputPin(Float,_T("AI.05"));
	AddOutputPin(Float,_T("AI.06"));
	AddOutputPin(Float,_T("AI.07"));
	AddOutputPin(Float,_T("AI.08"));
	AddOutputPin(Float,_T("AI.09"));
	AddOutputPin(Float,_T("AI.10"));
	m_NetworkID = 0;
}
