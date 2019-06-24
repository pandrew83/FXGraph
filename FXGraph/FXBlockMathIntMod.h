#pragma once
#include "fxblock.h"
class CFXBlockMathIntMod :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathIntMod);
	void Create(CFXObject* pObject);
	bool Calc();
	CFXBlockMathIntMod(void);
	~CFXBlockMathIntMod(void);
};

