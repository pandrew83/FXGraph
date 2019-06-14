#pragma once
#include "fxblock.h"
class CFXBlockMathPow :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathPow);
	CFXBlockMathPow(void);
	CFXBlockMathPow(CFXBlock* pBlock);
	bool Calc();
	~CFXBlockMathPow(void);
	int GetClassID() {
		return BLOCK_MATH_POW;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockMathPow");
	}
};

