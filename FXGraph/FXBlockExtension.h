#pragma once
#include "fxblock.h"
class CFXBlockExtension :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockExtension);
	CFXBlockExtension(void);
	CFXBlockExtension(CFXBlock* pBlock) : CFXBlock(pBlock){
	}
	~CFXBlockExtension(void);
	CFXPin* AddInputPin(CFXPinType type, CString funcName);
	CFXPin* AddOutputPin(CFXPinType type, CString funcName);
};

