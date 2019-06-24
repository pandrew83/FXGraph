#pragma once
#include "fxblock.h"
class CFXBlockMathBitwiseNot :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathBitwiseNot);
	CFXBlockMathBitwiseNot(void);
	void Create(CFXObject* pObject);
	~CFXBlockMathBitwiseNot(void);
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};

