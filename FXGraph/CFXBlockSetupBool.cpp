#include "stdafx.h"
#include "CFXBlockSetupBool.h"
IMPLEMENT_SERIAL(CFXBlockSetupBool, CFXBlock, 1);

CFXBlockSetupBool::CFXBlockSetupBool()
{
}

CFXBlockSetupBool::~CFXBlockSetupBool()
{
}

void CFXBlockSetupBool::Initialize()
{
	CFXBlock::Initialize();
}

void CFXBlockSetupBool::Create(CFXObject* pObject)
{
	CFXBlock::Create(pObject);
	m_MinHeight = 50;
	m_Height = 50;
	m_Name = _T("Уставка");
	m_OutputPinTypes.AddTail(Logical);
	m_PinOutMinCount = 1;
	m_PinOutMaxCount = 1;
	AddOutputPin(Logical, _T("Output"), true, true, true);
}

bool CFXBlockSetupBool::Calc()
{
	if (!CFXBlock::Calc())
		return false;
	return true;
}
