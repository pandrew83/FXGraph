#pragma once
#include "FXBlock.h"

class CFXBlockMathIntAdd : public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathIntAdd);
	CFXBlockMathIntAdd(void);
	void Create(CFXObject* pObject);
	~CFXBlockMathIntAdd(void);
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};

