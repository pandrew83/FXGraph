#include "stdafx.h"
#include "CFXBlockSetupLogical.h"
IMPLEMENT_SERIAL(CFXBlockSetupLogical, CFXBlock, 1);

CFXBlockSetupLogical::CFXBlockSetupLogical()
{
}

CFXBlockSetupLogical::~CFXBlockSetupLogical()
{
}

void CFXBlockSetupLogical::Initialize()
{
	CFXBlock::Initialize();
}

void CFXBlockSetupLogical::Create(CFXObject* pObject)
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

bool CFXBlockSetupLogical::Calc()
{
	if (!CFXBlock::Calc())
		return false;
	return true;
}
