#include "StdAfx.h"
#include "FXBlockMathIntDiv.h"
IMPLEMENT_SERIAL(CFXBlockMathIntDiv,CFXBlock,1);


CFXBlockMathIntDiv::CFXBlockMathIntDiv(void)
{
}


CFXBlockMathIntDiv::~CFXBlockMathIntDiv(void)
{
}

void CFXBlockMathIntDiv::Create(CFXObject* pObject)
{
	CFXBlock::Create(pObject);
	m_Name = "X / Y";
	m_PinInMinCount = 2;
	m_PinInMaxCount = 32;
	m_PinOutMinCount = 1;
	m_PinOutMaxCount = 1;
	m_InputPinTypes.AddTail(Int);
	m_OutputPinTypes.AddTail(Int);
	AddInputPin(Int, _T("x"));
	AddInputPin(Int, _T("y"));
	AddOutputPin(Int, _T("z"));
}

bool CFXBlockMathIntDiv::Calc(void)
{
	if (!CFXBlock::Calc())
		return false;
	ASSERT(m_InputPins.GetCount() == 2 && m_OutputPins.GetCount() == 1);

	POSITION pos = m_InputPins.GetHeadPosition();
	CFXPin* pPin1 = m_InputPins.GetNext(pos);
	CFXPin* pPin2 = m_InputPins.GetNext(pos);
	CFXPin* pPinOut = m_OutputPins.GetHead();
	pPinOut->SetValue( (int)pPin1->GetValue() / (int)pPin2->GetValue() );
	return true;
}
