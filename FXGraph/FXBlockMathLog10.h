#pragma once
#include "fxblock.h"
class CFXBlockMathLog10 :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathLog10);
	CFXBlockMathLog10(void);
	void Create(CFXObject* pObject);
	bool Calc();
	~CFXBlockMathLog10(void);
};

