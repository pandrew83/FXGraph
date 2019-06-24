#pragma once
#include "fxblock.h"
class CFXBlockMathTan :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathTan);
	CFXBlockMathTan(void);
	void Create(CFXObject* pObject);
	bool Calc();
	~CFXBlockMathTan(void);
};

