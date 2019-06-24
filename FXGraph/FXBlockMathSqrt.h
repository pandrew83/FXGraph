#pragma once
#include "fxblock.h"
class CFXBlockMathSqrt :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathSqrt);
	CFXBlockMathSqrt(void);
	void Create(CFXObject* pObject);
	bool Calc();
	~CFXBlockMathSqrt(void);
};

