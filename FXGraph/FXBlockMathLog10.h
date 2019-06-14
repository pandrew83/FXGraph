#pragma once
#include "fxblock.h"
class CFXBlockMathLog10 :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathLog10);
	CFXBlockMathLog10(void);
	CFXBlockMathLog10(CFXBlock* pBlock);
	bool Calc();
	~CFXBlockMathLog10(void);
	int GetClassID() {
		return BLOCK_MATH_LOG10;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockMathLog10");
	}
};

