#pragma once
#include "fxblock.h"
class CFXBlockMathFloatGreatEqual :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathFloatGreatEqual);
	CFXBlockMathFloatGreatEqual(void);
	CFXBlockMathFloatGreatEqual(CFXBlock* pBlock);
	~CFXBlockMathFloatGreatEqual(void);
	bool Calc(void);
};

