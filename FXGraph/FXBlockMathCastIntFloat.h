#pragma once
#include "fxblock.h"
class CFXBlockMathCastIntFloat :
	public CFXBlock
{
public:
	CFXBlockMathCastIntFloat(void);
	DECLARE_SERIAL(CFXBlockMathCastIntFloat);
	CFXBlockMathCastIntFloat(CFXBlock* pBlock);
	~CFXBlockMathCastIntFloat(void);
	int GetClassID(){
		return BLOCK_MATH_CAST_INT_FLOAT;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockMathCastIntFloat");
	}
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};

