#pragma once
#include "fxblock.h"
class CFXBlockMathIntLess :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathIntLess);
	CFXBlockMathIntLess(void);
	CFXBlockMathIntLess(CFXBlock*pBlock);
	bool Calc();
	~CFXBlockMathIntLess(void);
};

