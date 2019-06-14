#pragma once
#include "fxblock.h"
class CFXBlockLogicalTriggerSR :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockLogicalTriggerSR);
	CFXBlockLogicalTriggerSR(void);
	CFXBlockLogicalTriggerSR(CFXBlock* pBlock);
	bool Calc();
	bool m_Prev;
	~CFXBlockLogicalTriggerSR(void);
	void Initialize(void);
	int GetClassID() {
		return BLOCK_LOGICAL_TRIGGER_SR;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockLogicalTriggerSR");
	}
};

