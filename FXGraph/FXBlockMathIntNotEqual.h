#pragma once
#include "fxblock.h"
class CFXBlockMathIntNotEqual :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathIntNotEqual);
	CFXBlockMathIntNotEqual(CFXBlock* pBlock);
	bool Calc();
	CFXBlockMathIntNotEqual(void);
	~CFXBlockMathIntNotEqual(void);
};

