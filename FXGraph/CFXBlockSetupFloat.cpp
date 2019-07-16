#include "stdafx.h"
#include "CFXBlockSetupFloat.h"
IMPLEMENT_SERIAL(CFXBlockSetupFloat,CFXBlock,1);

CFXBlockSetupFloat::CFXBlockSetupFloat()
{
}

CFXBlockSetupFloat::~CFXBlockSetupFloat()
{
}

void CFXBlockSetupFloat::Initialize()
{
	CFXBlock::Initialize();
}

void CFXBlockSetupFloat::Create(CFXObject* pObject)
{
	CFXBlock::Create(pObject);
	m_MinHeight = 50;
	m_Height = 50;
	m_Name = _T("Уставка");
	m_OutputPinTypes.AddTail(Float);
	m_PinOutMaxCount = 1;
	m_PinOutMinCount = 1;
	AddOutputPin(Float, _T("Output"), true, true, true);
}

bool CFXBlockSetupFloat::Calc()
{
	if (!CFXBlock::Calc())
		return false;
	return true;
}
