#pragma once
#include "fxblock.h"
class CFXBlockMathFloatNotEqual :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathFloatNotEqual);
	CFXBlockMathFloatNotEqual(void);
	CFXBlockMathFloatNotEqual(CFXBlock* pBlock);
	~CFXBlockMathFloatNotEqual(void);
	bool Calc(void);
};

