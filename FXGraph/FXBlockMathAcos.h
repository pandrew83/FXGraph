#pragma once
#include "fxblock.h"
class CFXBlockMathAcos :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathAcos);
	CFXBlockMathAcos(void);
	CFXBlockMathAcos(CFXBlock* pBlock);
	bool Calc();
	~CFXBlockMathAcos(void);
	int GetClassID() {
		return BLOCK_MATH_ACOS;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockMathAcos");
	}
};

