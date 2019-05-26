#pragma once
#include "fxblock.h"
class CFXBlockMathFloatGreat :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathFloatGreat);
	CFXBlockMathFloatGreat(void);
	~CFXBlockMathFloatGreat(void);
	CFXBlockMathFloatGreat(CFXBlock* pBlock);
	bool Calc(void);
};

