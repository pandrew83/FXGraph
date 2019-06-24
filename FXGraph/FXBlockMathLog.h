#pragma once
#include "fxblock.h"
class CFXBlockMathLog :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathLog);
	CFXBlockMathLog(void);
	void Create(CFXObject* pObject);
	bool Calc();
	~CFXBlockMathLog(void);
};

