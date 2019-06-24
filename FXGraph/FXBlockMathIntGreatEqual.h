#pragma once
#include "fxblock.h"
class CFXBlockMathIntGreatEqual :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathIntGreatEqual);
	CFXBlockMathIntGreatEqual(void);
	void Create(CFXObject* pObject);
	bool Calc();
	~CFXBlockMathIntGreatEqual(void);
};

