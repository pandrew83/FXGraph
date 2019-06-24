#pragma once
#include "fxblock.h"
class CFXBlockMathFloatSub :
	public CFXBlock
{
public:
	CFXBlockMathFloatSub(void);
	DECLARE_SERIAL(CFXBlockMathFloatSub);
	void Create(CFXObject* pObject);
	~CFXBlockMathFloatSub(void);
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};

