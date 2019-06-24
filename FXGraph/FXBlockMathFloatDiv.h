#pragma once
#include "fxblock.h"
class CFXBlockMathFloatDiv :
	public CFXBlock
{
public:
	CFXBlockMathFloatDiv(void);
	DECLARE_SERIAL(CFXBlockMathFloatDiv);
	void Create(CFXObject* pObject);
	~CFXBlockMathFloatDiv(void);
	bool Calc(void);
};

