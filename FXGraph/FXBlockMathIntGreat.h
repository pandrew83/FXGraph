#pragma once
#include "fxblock.h"
class CFXBlockMathIntGreat :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathIntGreat);
	CFXBlockMathIntGreat(void);
	CFXBlockMathIntGreat(CFXBlock* pBlock);
	bool Calc();
	~CFXBlockMathIntGreat(void);
};

