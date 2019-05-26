#pragma once
#include "fxblock.h"
class CFXBlockMathLog :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathLog);
	CFXBlockMathLog(void);
	CFXBlockMathLog(CFXBlock* pBlock);
	bool Calc();
	~CFXBlockMathLog(void);
};

