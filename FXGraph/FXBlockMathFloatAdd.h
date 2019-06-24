#pragma once
#include "fxblock.h"
class CFXBlockMathFloatAdd :
	public CFXBlock
{
public:
	CFXBlockMathFloatAdd(void);
	DECLARE_SERIAL(CFXBlockMathFloatAdd);
	void Create(CFXObject* pObject);
	~CFXBlockMathFloatAdd(void);
	int GetClassID(){
		return BLOCK_MATH_FLOAT_ADD;
	}
	bool Calc(void);
};

