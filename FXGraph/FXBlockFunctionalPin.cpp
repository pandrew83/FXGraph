#include "StdAfx.h"
#include "FXBlockFunctionalPin.h"
#include "FXGraphDoc.h"
#include "FXBlockFunctional.h"

IMPLEMENT_SERIAL(CFXBlockFunctionalPin,CFXBlock,1)

CFXBlockFunctionalPin::CFXBlockFunctionalPin(void)
{
}


CFXBlockFunctionalPin::~CFXBlockFunctionalPin(void)
{
}

CFXBlockFunctionalPin::CFXBlockFunctionalPin(CFXBlock* pBlock,CFXPin* pLinkedPin) : CFXBlock(){
	CFXBlock::Create(pBlock);
	m_Height = 50;
	m_bCalc = false;
	m_pLinkedPin = pLinkedPin;
	m_Name = "FuncPin";//pLinkedPin->m_Name;
	CFXPin* pPin = pLinkedPin;
	if (pLinkedPin->m_Dir == Input){
		m_OutputPinTypes.AddTail(pLinkedPin->m_Type);
		pPin = AddOutputPin(pLinkedPin->m_Type,pLinkedPin->GetFuncName(),false,false);
	}
	else{
		m_InputPinTypes.AddTail(pLinkedPin->m_Type);
		pPin = AddInputPin(pLinkedPin->m_Type,pLinkedPin->GetFuncName(),false,false,false);
	}
	pPin->SetName(pLinkedPin->GetName());
	pPin->m_bConst = pLinkedPin->m_bConst;
	pPin->SetValue( pLinkedPin->GetValue() );
}

void CFXBlockFunctionalPin::Serialize(CArchive& ar){
	CFXBlock::Serialize(ar);
	if (ar.IsStoring()){
		if (m_pLinkedPin)
			ar << m_pLinkedPin->m_ID;
		else
			ar << (int)0;
	}
	else{
		int id;
		ar >> id;
		m_pLinkedPin = (CFXPin*)id;
	}
}

bool CFXBlockFunctionalPin::Calc(void)
{
	if (!CFXBlock::Calc())
		return false;
	
	POSITION pos = m_InputPins.GetHeadPosition();
	while (pos){
		CFXPin* pPin = m_InputPins.GetNext(pos);
		m_pLinkedPin->SetValue(pPin->GetValue());
	}

	pos = m_OutputPins.GetHeadPosition();
	while (pos){
		CFXPin* pPin = m_OutputPins.GetNext(pos);
		pPin->SetValue(m_pLinkedPin->GetValue());
	}
	return true;
}


void CFXBlockFunctionalPin::AfterSerialize(void)
{
	ASSERT(m_pBlock);
	m_pLinkedPin = dynamic_cast<CFXPin*>(m_pBlock->GetByID((int)m_pLinkedPin));
}


bool CFXBlockFunctionalPin::IsRemovable()
{
	return false;
}
