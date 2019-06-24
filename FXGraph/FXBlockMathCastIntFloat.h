#pragma once
#include "fxblock.h"
class CFXBlockMathCastIntFloat :
	public CFXBlock
{
public:
	CFXBlockMathCastIntFloat(void);
	DECLARE_SERIAL(CFXBlockMathCastIntFloat);
	void Create(CFXObject* pObject);
	~CFXBlockMathCastIntFloat(void);
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};

