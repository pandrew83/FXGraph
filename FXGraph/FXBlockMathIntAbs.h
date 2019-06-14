#pragma once
#include "fxblock.h"
class CFXBlockMathIntAbs :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathIntAbs);
	CFXBlockMathIntAbs(void);
	CFXBlockMathIntAbs(CFXBlock* pBlock);
	bool Calc();
	~CFXBlockMathIntAbs(void);
	int GetClassID() {
		return BLOCK_MATH_INT_ABS;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockMathIntAbs");
	}
};

