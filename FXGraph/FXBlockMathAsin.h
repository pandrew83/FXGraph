#pragma once
#include "fxblock.h"
class CFXBlockMathAsin :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathAsin);
	CFXBlockMathAsin(void);
	void Create(CFXObject* pObject);
	bool Calc();
	~CFXBlockMathAsin(void);
};

