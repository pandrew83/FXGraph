#pragma once
#include "fxblock.h"
class CFXBlockMathExp :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathExp);
	CFXBlockMathExp(void);
	CFXBlockMathExp(CFXBlock* pBlock);
	bool Calc();
	~CFXBlockMathExp(void);
	int GetClassID() {
		return BLOCK_MATH_EXP;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockMathExp");
	}
};

