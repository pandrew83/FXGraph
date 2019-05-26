#pragma once
#include "FXBlock.h"

class CFXBlockMathIntAdd : public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathIntAdd);
	CFXBlockMathIntAdd(void);
	CFXBlockMathIntAdd(CFXBlock* pBlock);
	~CFXBlockMathIntAdd(void);
	int GetClassID(){
		return BLOCK_MATH_INT_ADD;
	}
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};

