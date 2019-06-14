#pragma once
#include "fxblock.h"
class CFXBlockMathAtan :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathAtan);
	CFXBlockMathAtan(void);
	CFXBlockMathAtan(CFXBlock* pBlock);
	bool Calc();
	~CFXBlockMathAtan(void);
	int GetClassID() {
		return BLOCK_MATH_ATAN;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockMathAtan");
	}
};

