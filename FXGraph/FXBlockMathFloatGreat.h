#pragma once
#include "fxblock.h"
class CFXBlockMathFloatGreat :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathFloatGreat);
	CFXBlockMathFloatGreat(void);
	~CFXBlockMathFloatGreat(void);
	CFXBlockMathFloatGreat(CFXBlock* pBlock);
	bool Calc(void);
	int GetClassID() {
		return BLOCK_MATH_FLOAT_GREAT;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockMathFloatGreat");
	}
};

