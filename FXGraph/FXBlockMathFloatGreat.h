#pragma once
#include "fxblock.h"
class CFXBlockMathFloatGreat :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathFloatGreat);
	CFXBlockMathFloatGreat(void);
	void Create(CFXObject* pObject);
	~CFXBlockMathFloatGreat(void);
	bool Calc(void);
};

