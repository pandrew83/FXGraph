#pragma once
#include "fxblock.h"
class CFXBlockMathFloatMul :
	public CFXBlock
{
public:
	CFXBlockMathFloatMul(void);
	DECLARE_SERIAL(CFXBlockMathFloatMul);
	CFXBlockMathFloatMul(CFXBlock* pBlock);
	~CFXBlockMathFloatMul(void);
	int GetClassID(){
		return BLOCK_MATH_FLOAT_MUL;
	}
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};
