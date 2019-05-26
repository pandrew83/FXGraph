#pragma once
#include "fxblock.h"
class CFXBlockMathCos :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathCos);
	CFXBlockMathCos(void);
	CFXBlockMathCos(CFXBlock* pBlock);
	bool Calc();
	~CFXBlockMathCos(void);
};

