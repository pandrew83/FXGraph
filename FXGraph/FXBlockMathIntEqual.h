#pragma once
#include "fxblock.h"
class CFXBlockMathIntEqual :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathIntEqual);
	CFXBlockMathIntEqual(void);
	void Create(CFXObject* pObject);
	bool Calc();
	~CFXBlockMathIntEqual(void);
};

