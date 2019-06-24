#pragma once
#include "fxblock.h"
class CFXBlockMathBitwiseOr :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathBitwiseOr);
	CFXBlockMathBitwiseOr(void);
	void Create(CFXObject* pObject);
	~CFXBlockMathBitwiseOr(void);
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};

