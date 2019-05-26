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
};

