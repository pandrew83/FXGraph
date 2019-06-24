#pragma once
#include "fxblock.h"
class CFXBlockMathFloatAbs :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathFloatAbs);
	CFXBlockMathFloatAbs(void);
	void Create(CFXObject* pObject);
	bool Calc();
	~CFXBlockMathFloatAbs(void);
};

