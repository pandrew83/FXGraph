#pragma once
#include "fxblock.h"
class CFXBlockMathSin :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathSin);
	CFXBlockMathSin(void);
	CFXBlockMathSin(CFXBlock* pBlock);
	bool Calc();
	~CFXBlockMathSin(void);
};

