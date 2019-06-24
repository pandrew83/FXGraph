#pragma once
#include "fxblock.h"
class CFXBlockLogicalTriggerRS :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockLogicalTriggerRS);
	CFXBlockLogicalTriggerRS(void);
	void Create(CFXObject* pObject);
	bool Calc();
	bool m_Prev;
	~CFXBlockLogicalTriggerRS(void);
	void Initialize(void);
};

