#pragma once
#include "fxblock.h"
class CFXBlockMathAcos :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathAcos);
	CFXBlockMathAcos(void);
	CFXBlockMathAcos(CFXBlock* pBlock);
	bool Calc();
	~CFXBlockMathAcos(void);
};

