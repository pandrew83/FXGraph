#pragma once
#include "fxblock.h"
class CFXBlockMathAtan :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathAtan);
	CFXBlockMathAtan(void);
	void Create(CFXObject* pObject);
	bool Calc();
	~CFXBlockMathAtan(void);
};

