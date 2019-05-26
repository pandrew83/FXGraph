#pragma once
#include "fxblock.h"
class CFXBlockMathFloatLessEqual :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathFloatLessEqual);
	CFXBlockMathFloatLessEqual(void);
	CFXBlockMathFloatLessEqual(CFXBlock* pBlock);
	~CFXBlockMathFloatLessEqual(void);
	bool Calc(void);
};

