#pragma once
#include "fxblock.h"
class CFXBlockLogicalFronts :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockLogicalFronts);
	void Create(CFXObject* pObject);
	bool Calc();
	CFXBlockLogicalFronts(void);
	~CFXBlockLogicalFronts(void);
	bool m_Prev;
	void Initialize(void);
};

