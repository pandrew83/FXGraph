#include "stdafx.h"
#include "CFXBlockDemoTu154.h"
IMPLEMENT_SERIAL(CFXBlockDemoTu154, CFXBlock, 1);

CFXBlockDemoTu154::CFXBlockDemoTu154()
{
}

CFXBlockDemoTu154::~CFXBlockDemoTu154()
{
}

void CFXBlockDemoTu154::Create(CFXObject* pObject)
{
	CFXBlock::Create(pObject);
	m_Name = _T("Ту-154");
	m_InputPinTypes.AddTail(Float);
	m_OutputPinTypes.AddTail(Float);
	AddInputPin(Float, _T("Масса"));
//	AddInputPin(Float,_T("
}

bool CFXBlockDemoTu154::Calc()
{
	if (!CFXBlock::Calc())
		return false;
	return true;
}

void CFXBlockDemoTu154::Initialize()
{
}
