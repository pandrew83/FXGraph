#pragma once
#include "fxblock.h"
class CFXBlockMathFloatRound :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathFloatRound);
	CFXBlockMathFloatRound(void);
	CFXBlockMathFloatRound(CFXBlock* pBlock);
	bool Calc();
	~CFXBlockMathFloatRound(void);
};

