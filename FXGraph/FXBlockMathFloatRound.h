#pragma once
#include "fxblock.h"
class CFXBlockMathFloatRound :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathFloatRound);
	CFXBlockMathFloatRound(void);
	void Create(CFXObject* pObject);
	bool Calc();
	~CFXBlockMathFloatRound(void);
};

