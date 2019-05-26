#pragma once
#include "fxblock.h"
class CFXBlockMathAsin :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathAsin);
	CFXBlockMathAsin(void);
	CFXBlockMathAsin(CFXBlock* pBlock);
	bool Calc();
	~CFXBlockMathAsin(void);
};

