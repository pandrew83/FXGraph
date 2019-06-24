#pragma once
#include "fxblock.h"
class CFXBlockMathCastFloatInt :
	public CFXBlock
{
public:
	CFXBlockMathCastFloatInt(void);
	DECLARE_SERIAL(CFXBlockMathCastFloatInt);
	void Create(CFXObject* pObject);
	~CFXBlockMathCastFloatInt(void);
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};

