#pragma once
#include "fxblock.h"
class CFXBlockMathCastFloatInt :
	public CFXBlock
{
public:
	CFXBlockMathCastFloatInt(void);
	DECLARE_SERIAL(CFXBlockMathCastFloatInt);
	CFXBlockMathCastFloatInt(CFXBlock* pBlock);
	~CFXBlockMathCastFloatInt(void);
	int GetClassID(){
		return BLOCK_MATH_CAST_FLOAT_INT;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockMathCastFloatInt");
	}
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};

