#pragma once
#include "fxblock.h"
class CFXBlockMathIntEqual :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathIntEqual);
	CFXBlockMathIntEqual(void);
	CFXBlockMathIntEqual(CFXBlock* pBlock);
	bool Calc();
	~CFXBlockMathIntEqual(void);
};

