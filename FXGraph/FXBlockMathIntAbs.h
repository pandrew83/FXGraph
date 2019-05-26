#pragma once
#include "fxblock.h"
class CFXBlockMathIntAbs :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathIntAbs);
	CFXBlockMathIntAbs(void);
	CFXBlockMathIntAbs(CFXBlock* pBlock);
	bool Calc();
	~CFXBlockMathIntAbs(void);
};

