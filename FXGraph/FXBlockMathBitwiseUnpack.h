#pragma once
#include "fxblock.h"
class CFXBlockMathBitwiseUnpack :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathBitwiseUnpack);
	CFXBlockMathBitwiseUnpack(void);
	CFXBlockMathBitwiseUnpack(CFXBlock* pBlock);
	~CFXBlockMathBitwiseUnpack(void);
	int GetClassID(){
		return BLOCK_MATH_BITWISE_UNPACK;
	}
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};

