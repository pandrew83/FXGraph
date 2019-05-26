#pragma once
#include "fxblock.h"
class CFXBlockMathIntLessEqual :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathIntLessEqual);
	CFXBlockMathIntLessEqual(void);
	CFXBlockMathIntLessEqual(CFXBlock*pBlock);
	bool Calc();
	~CFXBlockMathIntLessEqual(void);
};

