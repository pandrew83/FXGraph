#pragma once
#include "fxblock.h"
class CFXBlockMathAcos :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathAcos);
	CFXBlockMathAcos(void);
	void Create(CFXObject* pObject);
	bool Calc();
	~CFXBlockMathAcos(void);
};

