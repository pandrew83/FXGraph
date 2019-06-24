#pragma once
#include "fxblock.h"
class CFXBlockMathExp :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathExp);
	CFXBlockMathExp(void);
	void Create(CFXObject* pObject);
	bool Calc(void);
	~CFXBlockMathExp(void);
};

