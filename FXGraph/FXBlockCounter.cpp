#include "StdAfx.h"
#include "FXBlockCounter.h"
IMPLEMENT_SERIAL(CFXBlockCounter,CFXBlock,1);

CFXBlockCounter::CFXBlockCounter(void)
{
}

CFXBlockCounter::CFXBlockCounter(CFXBlock* pBlock):CFXBlock(pBlock){
	m_Name = "CNTR";
	m_MinHeight = 150;
	m_Height = 150;
	m_InputPinTypes.AddTail(Logical);
	m_InputPinTypes.AddTail(Int);
	m_OutputPinTypes.AddTail(Logical);
	m_OutputPinTypes.AddTail(Int);
	m_PinInMinCount = 5;
	m_PinInMaxCount = 5;
	m_PinOutMinCount = 5;
	m_PinOutMaxCount = 5;
	AddInputPin(Logical,_T("Reset"));
	AddInputPin(Logical,_T("Load"));
	AddInputPin(Logical,_T("Inc"));
	AddInputPin(Logical,_T("Dec"));
	AddInputPin(Int,_T("DI"));
	AddOutputPin(Int,_T("DO"));
	AddOutputPin(Logical,_T("QU"));
	AddOutputPin(Logical,_T("QD"));
	AddOutputPin(Logical,_T("EU"));
	AddOutputPin(Logical,_T("ED"));
}

bool CFXBlockCounter::Calc(){
	if (!CFXBlock::Calc())
		return false;
	POSITION pos = m_InputPins.GetHeadPosition();
	bool reset = m_InputPins.GetNext(pos)->GetValue();
	bool load = m_InputPins.GetNext(pos)->GetValue();
	bool inc = m_InputPins.GetNext(pos)->GetValue();
	bool dec = m_InputPins.GetNext(pos)->GetValue();
	int di = m_InputPins.GetNext(pos)->GetValue();
	bool eu = false;
	bool ed = false;
	bool qu = false;
	bool qd = false;
	if (load)
		m_do = di;
	else
		if (dec && m_do > 0){
			m_do -= 1;
			qd = true;
		}
	if (reset)
		m_do = 0;
	else
		if (inc && m_do < di){
			m_do += 1;
			qu = true;
		}
	
	eu = m_do == di;
	ed = m_do == 0;

	pos = m_OutputPins.GetHeadPosition();
	CFXPin* pPin_do = m_OutputPins.GetNext(pos);
	CFXPin* pPin_qu = m_OutputPins.GetNext(pos);
	CFXPin* pPin_qd = m_OutputPins.GetNext(pos);
	CFXPin* pPin_eu = m_OutputPins.GetNext(pos);
	CFXPin* pPin_ed = m_OutputPins.GetNext(pos);
	pPin_do->SetValue(m_do);
	pPin_qu->SetValue(qu);
	pPin_qd->SetValue(qd);
	pPin_eu->SetValue(eu);
	pPin_ed->SetValue(ed);
	return true;
}

CFXBlockCounter::~CFXBlockCounter(void)
{
}


bool CFXBlockCounter::Check(void)
{
	if (!CFXBlock::Check())
		return false;
	POSITION pos = m_InputPins.GetHeadPosition();
	bool reset = m_InputPins.GetNext(pos)->GetValue();
	bool load = m_InputPins.GetNext(pos)->GetValue();
	bool inc = m_InputPins.GetNext(pos)->GetValue();
	bool dec = m_InputPins.GetNext(pos)->GetValue();
	int di = m_InputPins.GetNext(pos)->GetValue();

	if (inc == dec){
		CString msg;
		msg.Format(_T("Ѕлок #%d (%s): блок должен быть в одном из режимов inc или dec"),m_ID,m_Name);
		Log(Debug,msg);
		return false;
	}
	return true;
}


void CFXBlockCounter::Initialize(void)
{
	m_do = 0;
}
