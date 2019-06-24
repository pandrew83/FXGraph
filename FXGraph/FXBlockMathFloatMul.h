#pragma once
#include "fxblock.h"
class CFXBlockMathFloatMul :
	public CFXBlock
{
public:
	CFXBlockMathFloatMul(void);
	DECLARE_SERIAL(CFXBlockMathFloatMul);
	void Create(CFXObject* pObject);
	~CFXBlockMathFloatMul(void);
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};

