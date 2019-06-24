#pragma once
#include "fxblock.h"

class CFXBlockLogicalAnd : public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockLogicalAnd)
	CFXBlockLogicalAnd(void);
	void Create(CFXObject* pObject);
	~CFXBlockLogicalAnd(void);
	bool Calc(void);
};

