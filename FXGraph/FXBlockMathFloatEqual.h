#pragma once
#include "fxblock.h"
class CFXBlockMathFloatEqual :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathFloatEqual);
	CFXBlockMathFloatEqual(void);
	void Create(CFXObject* pObject);
	~CFXBlockMathFloatEqual(void);
	bool Calc(void);
};

