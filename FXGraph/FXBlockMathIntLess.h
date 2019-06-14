#pragma once
#include "fxblock.h"
class CFXBlockMathIntLess :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathIntLess);
	CFXBlockMathIntLess(void);
	CFXBlockMathIntLess(CFXBlock*pBlock);
	bool Calc();
	~CFXBlockMathIntLess(void);
	int GetClassID() {
		return BLOCK_MATH_INT_LESS;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockMathIntLess");
	}
};

