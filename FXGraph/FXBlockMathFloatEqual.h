#pragma once
#include "fxblock.h"
class CFXBlockMathFloatEqual :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathFloatEqual);
	CFXBlockMathFloatEqual(void);
	CFXBlockMathFloatEqual(CFXBlock* pBlock);
	~CFXBlockMathFloatEqual(void);
	bool Calc(void);
};

