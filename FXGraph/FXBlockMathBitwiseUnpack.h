#pragma once
#include "fxblock.h"
class CFXBlockMathBitwiseUnpack :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathBitwiseUnpack);
	CFXBlockMathBitwiseUnpack(void);
	void Create(CFXObject* pObject);
	~CFXBlockMathBitwiseUnpack(void);
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};

