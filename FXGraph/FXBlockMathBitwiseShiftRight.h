#pragma once
#include "fxblock.h"

class CFXBlockMathBitwiseShiftRight :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathBitwiseShiftRight);
	CFXBlockMathBitwiseShiftRight(void);
	void Create(CFXObject* pObject);
	~CFXBlockMathBitwiseShiftRight(void);
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};

