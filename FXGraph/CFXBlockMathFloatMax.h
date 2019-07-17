#pragma once
#include "FXBlock.h"
class CFXBlockMathFloatMax :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathFloatMax);
	CFXBlockMathFloatMax();
	~CFXBlockMathFloatMax();
	bool Calc();
	void Create(CFXObject* pObject);
};

