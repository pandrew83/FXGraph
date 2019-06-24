#pragma once
#include "fxblock.h"
class CFXBlockMathFloatLessEqual :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathFloatLessEqual);
	CFXBlockMathFloatLessEqual(void);
	void Create(CFXObject* pObject);
	~CFXBlockMathFloatLessEqual(void);
	bool Calc(void);
};

