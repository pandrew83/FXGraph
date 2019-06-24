#include "StdAfx.h"
#include "FXBlockLogicalOr.h"
IMPLEMENT_SERIAL(CFXBlockLogicalOr,CFXBlock,1);


CFXBlockLogicalOr::CFXBlockLogicalOr(void)
{
}


CFXBlockLogicalOr::~CFXBlockLogicalOr(void)
{
}

void CFXBlockLogicalOr::Create(CFXObject* pObject)
{
	CFXBlock::Create(pObject);
	m_Name = "Or";
	m_PinInMinCount = 2;
	m_PinInMaxCount = 32;
	m_PinOutMinCount = 1;
	m_PinOutMaxCount = 1;
	m_InputPinTypes.AddTail(Logical);
	m_OutputPinTypes.AddTail(Logical);

	AddInputPin(Logical,_T("x"));
	AddInputPin(Logical,_T("y"));
	AddOutputPin(Logical,_T("z"));
}


bool CFXBlockLogicalOr::Calc(void)
{
	if (!CFXBlock::Calc())
		return false;
	bool value = false;
	POSITION pos = m_InputPins.GetHeadPosition();
	while (pos){
		CFXPin* pPin = m_InputPins.GetNext(pos);
		value = value || (bool)pPin->GetValue();
	}
	m_OutputPins.GetHead()->SetValue( value );
	return true;
}
