#pragma once
#include "fxblock.h"
class CFXBlockMathIntMul :
	public CFXBlock
{
public:
	CFXBlockMathIntMul(void);
	DECLARE_SERIAL(CFXBlockMathIntMul);
	void Create(CFXObject* pObject);
	~CFXBlockMathIntMul(void);
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};

