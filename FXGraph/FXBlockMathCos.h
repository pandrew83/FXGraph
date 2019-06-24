#pragma once
#include "fxblock.h"
class CFXBlockMathCos :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathCos);
	CFXBlockMathCos(void);
	void Create(CFXObject* pObject);
	bool Calc();
	~CFXBlockMathCos(void);
};

