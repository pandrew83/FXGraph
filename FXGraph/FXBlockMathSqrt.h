#pragma once
#include "fxblock.h"
class CFXBlockMathSqrt :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathSqrt);
	CFXBlockMathSqrt(void);
	CFXBlockMathSqrt(CFXBlock* pBlock);
	bool Calc();
	~CFXBlockMathSqrt(void);
};

