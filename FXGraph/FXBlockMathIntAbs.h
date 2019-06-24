#pragma once
#include "fxblock.h"
class CFXBlockMathIntAbs :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathIntAbs);
	CFXBlockMathIntAbs(void);
	void Create(CFXObject* pObject);
	bool Calc();
	~CFXBlockMathIntAbs(void);
};

