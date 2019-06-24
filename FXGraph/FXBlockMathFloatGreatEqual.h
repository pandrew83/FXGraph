#pragma once
#include "fxblock.h"
class CFXBlockMathFloatGreatEqual :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathFloatGreatEqual);
	CFXBlockMathFloatGreatEqual(void);
	void Create(CFXObject* pObject);
	~CFXBlockMathFloatGreatEqual(void);
	bool Calc(void);
};

