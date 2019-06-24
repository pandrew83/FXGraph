#pragma once
#include "fxblock.h"
class CFXBlockMathIntDiv :
	public CFXBlock
{
public:
	CFXBlockMathIntDiv(void);
	DECLARE_SERIAL(CFXBlockMathIntDiv);
	void Create(CFXObject* pObject);
	~CFXBlockMathIntDiv(void);
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};

