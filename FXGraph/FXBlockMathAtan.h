#pragma once
#include "fxblock.h"
class CFXBlockMathAtan :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathAtan);
	CFXBlockMathAtan(void);
	CFXBlockMathAtan(CFXBlock* pBlock);
	bool Calc();
	~CFXBlockMathAtan(void);
};

