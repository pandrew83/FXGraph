#pragma once
#include "fxblock.h"
class CFXBlockMathIntNotEqual :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathIntNotEqual);
	void Create(CFXObject* pObject);
	bool Calc();
	CFXBlockMathIntNotEqual(void);
	~CFXBlockMathIntNotEqual(void);
};

