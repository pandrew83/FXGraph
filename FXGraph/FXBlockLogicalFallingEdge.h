#pragma once
#include "fxblock.h"
class CFXBlockLogicalFallingEdge :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockLogicalFallingEdge);
	CFXBlockLogicalFallingEdge(void);
	void Create(CFXObject* pObject);
	bool Calc();
	bool m_Prev;
	~CFXBlockLogicalFallingEdge(void);
	void Initialize(void);
};

