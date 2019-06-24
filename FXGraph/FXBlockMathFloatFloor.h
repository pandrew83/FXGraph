#pragma once
#include "fxblock.h"
class CFXBlockMathFloatFloor :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathFloatFloor);
	CFXBlockMathFloatFloor(void);
	void Create(CFXObject* pObject);
	bool Calc();
	~CFXBlockMathFloatFloor(void);
};

