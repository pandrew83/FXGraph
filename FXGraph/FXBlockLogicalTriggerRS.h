#pragma once
#include "fxblock.h"
class CFXBlockLogicalTriggerRS :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockLogicalTriggerRS);
	CFXBlockLogicalTriggerRS(void);
	CFXBlockLogicalTriggerRS(CFXBlock* pBlock);
	bool Calc();
	bool m_Prev;
	~CFXBlockLogicalTriggerRS(void);
	void Initialize(void);
	int GetClassID() {
		return BLOCK_LOGICAL_TRIGGER_RS;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockLogicalTriggerRS");
	}
};

