#pragma once
#include "fxblock.h"
class CFXBlockMathIntLess :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathIntLess);
	CFXBlockMathIntLess(void);
	void Create(CFXObject* pObject);
	bool Calc();
	~CFXBlockMathIntLess(void);
};

