#pragma once
#include "fxblock.h"
class CFXBlockMathTan :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathTan);
	CFXBlockMathTan(void);
	CFXBlockMathTan(CFXBlock* pBlock);
	bool Calc();
	~CFXBlockMathTan(void);
};

