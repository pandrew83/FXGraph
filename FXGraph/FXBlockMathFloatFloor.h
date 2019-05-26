#pragma once
#include "fxblock.h"
class CFXBlockMathFloatFloor :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathFloatFloor);
	CFXBlockMathFloatFloor(void);
	CFXBlockMathFloatFloor(CFXBlock* pBlock);
	bool Calc();
	~CFXBlockMathFloatFloor(void);
};

