#pragma once
#include "FXBlock.h"
class CFXBlockMathFloatMin :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathFloatMin);
	CFXBlockMathFloatMin();
	~CFXBlockMathFloatMin();
	bool Calc();
	void Create(CFXObject* pObject);
};

