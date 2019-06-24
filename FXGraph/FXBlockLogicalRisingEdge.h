#pragma once
#include "fxblock.h"
class CFXBlockLogicalRisingEdge :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockLogicalRisingEdge);
	CFXBlockLogicalRisingEdge(void);
	void Create(CFXObject* pObject);
	~CFXBlockLogicalRisingEdge(void);
	bool Calc();
	bool m_Prev;
	void Initialize(void);
};

