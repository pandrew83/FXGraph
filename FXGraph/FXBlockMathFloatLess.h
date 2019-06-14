#pragma once
#include "fxblock.h"
class CFXBlockMathFloatLess :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathFloatLess);
	CFXBlockMathFloatLess(void);
	CFXBlockMathFloatLess(CFXBlock* pBlock);
	~CFXBlockMathFloatLess(void);
	bool Calc(void);
	int GetClassID() {
		return BLOCK_MATH_FLOAT_LESS;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockMathFloatLess");
	}
};

