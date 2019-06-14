#pragma once
#include "FXPin.h"
#define NCOLORS		123

class CFXGraphicVariable : public CObject {
public:
	DECLARE_SERIAL(CFXGraphicVariable);
	CFXGraphicVariable();
	CFXGraphicVariable(int id, CString name, CFXPinType type);
	int m_ID;
	COLORREF m_Color;
	CFXPinType m_Type;
	CString m_Name;
protected:
	void Serialize(CArchive& ar);
};
