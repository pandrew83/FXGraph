#pragma once
#include "fxblock.h"
class CFXBlockMathBitwiseXor :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathBitwiseXor);
	CFXBlockMathBitwiseXor(void);
	void Create(CFXObject* pObject);
	~CFXBlockMathBitwiseXor(void);
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};

