#pragma once
#include "fxblock.h"
class CFXBlockMathPow :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathPow);
	CFXBlockMathPow(void);
	void Create(CFXObject* pObject);
	bool Calc();
	~CFXBlockMathPow(void);
};

