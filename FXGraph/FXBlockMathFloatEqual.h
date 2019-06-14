#pragma once
#include "fxblock.h"
class CFXBlockMathFloatEqual :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathFloatEqual);
	CFXBlockMathFloatEqual(void);
	CFXBlockMathFloatEqual(CFXBlock* pBlock);
	~CFXBlockMathFloatEqual(void);
	bool Calc(void);
	int GetClassID() {
		return BLOCK_MATH_FLOAT_EQUAL;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockMathFloatEqual");
	}
};

