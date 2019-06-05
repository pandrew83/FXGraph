#pragma once
#include "FXPin.h"
class CFXGraphicVariable;

class CFXGraphic : public CObject
{
public:
	DECLARE_SERIAL(CFXGraphic);
	CFXGraphic();
	CString GetTitle() const {
		return m_Title;
	}
	virtual ~CFXGraphic();
	void SetTitle(CString title) { m_Title = title; }
	POSITION GetFirstVariable() const;
	CFXGraphicVariable* GetNextVariable(POSITION& pos);
	void AddVariable(int id, CString name, CFXPinType type);
protected:
	CString m_Title;
	CList<CFXGraphicVariable*> m_Vars;
	void Serialize(CArchive& ar);
public:
	void RemoveVariable(CFXGraphicVariable* pVar);
};

