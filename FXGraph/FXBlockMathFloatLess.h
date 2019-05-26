#pragma once
#include "fxblock.h"
class CFXBlockMathFloatLess :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathFloatLess);
	CFXBlockMathFloatLess(void);
	CFXBlockMathFloatLess(CFXBlock* pBlock);
	~CFXBlockMathFloatLess(void);
	bool Calc(void);
};

