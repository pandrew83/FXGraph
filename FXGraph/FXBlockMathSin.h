#pragma once
#include "fxblock.h"
class CFXBlockMathSin :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathSin);
	CFXBlockMathSin(void);
	CFXBlockMathSin(CFXBlock* pBlock);
	bool Calc();
	~CFXBlockMathSin(void);
	int GetClassID() {
		return BLOCK_MATH_SIN;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockMathSin");
	}
};

