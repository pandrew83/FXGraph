#include "stdafx.h"
#include "CFXGraphic.h"
#include "CFXGraphicVariable.h"
#include "FXPin.h"

IMPLEMENT_SERIAL(CFXGraphic, CObject, 1);

CFXGraphic::CFXGraphic()
{
	m_Title = "";
}

CFXGraphic::~CFXGraphic()
{
	POSITION pos = m_Vars.GetHeadPosition();
	while (pos) {
		CFXGraphicVariable* pVar = m_Vars.GetNext(pos);
		delete pVar;
	}
}

POSITION CFXGraphic::GetFirstVariable() const
{
	return m_Vars.GetHeadPosition();
}

CFXGraphicVariable* CFXGraphic::GetNextVariable(POSITION& pos)
{
	return m_Vars.GetNext(pos);
}

void CFXGraphic::AddVariable(int id, CString name, CFXPinType type)
{
	POSITION pos = m_Vars.GetHeadPosition();
	while (pos) {
		CFXGraphicVariable* pVar = m_Vars.GetNext(pos);
		if (pVar->m_ID == id) {
			return;
		}
	}
	CFXGraphicVariable* pVar = new CFXGraphicVariable(id, name, type);
	m_Vars.AddTail(pVar);
}

void CFXGraphic::Serialize(CArchive& ar)
{
	if (ar.IsStoring()) {
		ar << m_Title;
	}
	else {
		ar >> m_Title;
	}
}


void CFXGraphic::RemoveVariable(CFXGraphicVariable* pVar)
{
	POSITION pos = m_Vars.Find(pVar);
	if (pos) {
		m_Vars.RemoveAt(pos);
		delete pVar;
	}
}
