#pragma once
#include "fxblock.h"
class CFXBlockMathFloatAbs :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathFloatAbs);
	CFXBlockMathFloatAbs(void);
	CFXBlockMathFloatAbs(CFXBlock* pBlock);
	bool Calc();
	~CFXBlockMathFloatAbs(void);
	int GetClassID() {
		return BLOCK_MATH_FLOAT_ABS;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockMathFloatAbs");
	}
};

