#pragma once
#include "fxblock.h"
class CFXBlockMathIntSub :
	public CFXBlock
{
public:
	CFXBlockMathIntSub(void);
	DECLARE_SERIAL(CFXBlockMathIntSub);
	void Create(CFXObject* pObject);
	~CFXBlockMathIntSub(void);
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
	
};

