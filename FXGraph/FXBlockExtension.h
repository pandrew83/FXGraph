#pragma once
#include "fxblock.h"

class CFXBlockExtension :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockExtension);
	CFXBlockExtension(void);
//	void Create(CFXObject* pObject);
	~CFXBlockExtension(void);
	CFXPin* AddInputPin(CFXPinType type, CString funcName);
	CFXPin* AddOutputPin(CFXPinType type, CString funcName);
	void FillProperties(CPropertiesWnd* pWnd);
	void Serialize(CArchive& ar);
};

