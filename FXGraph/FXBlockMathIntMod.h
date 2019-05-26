#pragma once
#include "fxblock.h"
class CFXBlockMathIntMod :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathIntMod);
	CFXBlockMathIntMod(CFXBlock* pBlock);
	bool Calc();
	CFXBlockMathIntMod(void);
	~CFXBlockMathIntMod(void);
};

