#pragma once
#include "fxblock.h"
class CFXBlockMathBitwiseOr :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathBitwiseOr);
	CFXBlockMathBitwiseOr(void);
	CFXBlockMathBitwiseOr(CFXBlock* pBlock);
	~CFXBlockMathBitwiseOr(void);
	int GetClassID(){
		return BLOCK_MATH_BITWISE_OR;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockMathBitwiseOr");
	}
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};

