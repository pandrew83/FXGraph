#pragma once
#include "fxblock.h"
class CFXBlockMathPow :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathPow);
	CFXBlockMathPow(void);
	CFXBlockMathPow(CFXBlock* pBlock);
	bool Calc();
	~CFXBlockMathPow(void);
};

