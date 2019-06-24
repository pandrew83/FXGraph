#pragma once
#include "FXBlock.h"

class CFXBlockMathBitwiseShiftLeft : public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathBitwiseShiftLeft);
	CFXBlockMathBitwiseShiftLeft(void);
	void Create(CFXObject* pObject);
	~CFXBlockMathBitwiseShiftLeft(void);
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};

