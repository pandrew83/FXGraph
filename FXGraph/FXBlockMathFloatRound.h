#pragma once
#include "fxblock.h"
class CFXBlockMathFloatRound :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathFloatRound);
	CFXBlockMathFloatRound(void);
	CFXBlockMathFloatRound(CFXBlock* pBlock);
	bool Calc();
	~CFXBlockMathFloatRound(void);
	int GetClassID() {
		return BLOCK_MATH_FLOAT_ROUND;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockMathFloatRound");
	}
};

