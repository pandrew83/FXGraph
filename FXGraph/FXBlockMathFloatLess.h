#pragma once
#include "fxblock.h"
class CFXBlockMathFloatLess :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathFloatLess);
	CFXBlockMathFloatLess(void);
	void Create(CFXObject* pObject);
	~CFXBlockMathFloatLess(void);
	bool Calc(void);
};

