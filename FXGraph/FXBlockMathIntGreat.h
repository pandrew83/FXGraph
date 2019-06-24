#pragma once
#include "fxblock.h"
class CFXBlockMathIntGreat :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathIntGreat);
	CFXBlockMathIntGreat(void);
	void Create(CFXObject* pObject);
	bool Calc();
	~CFXBlockMathIntGreat(void);
};

