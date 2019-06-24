#pragma once
#include "fxblock.h"
class CFXBlockMathFloatNotEqual :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathFloatNotEqual);
	CFXBlockMathFloatNotEqual(void);
	void Create(CFXObject* pObject);
	~CFXBlockMathFloatNotEqual(void);
	bool Calc(void);
};

