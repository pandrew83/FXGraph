#include "stdafx.h"
#include "CFXBlockSetupInt.h"
IMPLEMENT_SERIAL(CFXBlockSetupInt, CFXBlock, 1);

CFXBlockSetupInt::CFXBlockSetupInt()
{
}

CFXBlockSetupInt::~CFXBlockSetupInt()
{
}

void CFXBlockSetupInt::Initialize()
{
	CFXBlock::Initialize();
}

void CFXBlockSetupInt::Create(CFXObject* pObject)
{
	CFXBlock::Create(pObject);
	m_MinHeight = 50;
	m_Height = 50;
	m_Name = _T("Уставка");
	m_OutputPinTypes.AddTail(Int);
	m_PinOutMinCount = 1;
	m_PinOutMaxCount = 1;
	AddOutputPin(Int, _T("Output"), true, true, true);
}

bool CFXBlockSetupInt::Calc()
{
	if (!CFXBlock::Calc())
		return false;
	return true;
}
