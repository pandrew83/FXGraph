#pragma once
#include "fxblock.h"
class CFXBlockMathIntLessEqual :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathIntLessEqual);
	CFXBlockMathIntLessEqual(void);
	void Create(CFXObject* pObject);
	bool Calc();
	~CFXBlockMathIntLessEqual(void);
};

