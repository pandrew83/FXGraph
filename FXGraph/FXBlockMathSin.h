#pragma once
#include "fxblock.h"
class CFXBlockMathSin :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathSin);
	CFXBlockMathSin(void);
	void Create(CFXObject* pObject);
	bool Calc();
	~CFXBlockMathSin(void);
};

