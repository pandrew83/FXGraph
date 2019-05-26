#pragma once
#include "fxblock.h"
class CFXBlockMathBitwiseAnd :
	public CFXBlock
{
public:
	CFXBlockMathBitwiseAnd(void);
	CFXBlockMathBitwiseAnd(CFXBlock* pBlock);
	~CFXBlockMathBitwiseAnd(void);
	int GetClassID(){
		return BLOCK_MATH_BITWISE_AND;
	}

	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};

