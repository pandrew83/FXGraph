#pragma once
#include "fxblock.h"
class CFXBlockLogicalTriggerRSRisingEdge :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockLogicalTriggerRSRisingEdge);
	CFXBlockLogicalTriggerRSRisingEdge(void);
	CFXBlockLogicalTriggerRSRisingEdge(CFXBlock* pBlock);
	bool Calc();
	bool m_PrevR;
	bool m_PrevS;
	bool m_PrevZ;
	~CFXBlockLogicalTriggerRSRisingEdge(void);
	void Initialize(void);
};

