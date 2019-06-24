#pragma once
#include "fxblock.h"
class CFXBlockMathBitwiseAnd :
	public CFXBlock
{
public:
	CFXBlockMathBitwiseAnd(void);
	void Create(CFXObject* pObject);
	~CFXBlockMathBitwiseAnd(void);
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};

