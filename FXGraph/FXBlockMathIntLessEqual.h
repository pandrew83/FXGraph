#pragma once
#include "fxblock.h"
class CFXBlockMathIntLessEqual :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathIntLessEqual);
	CFXBlockMathIntLessEqual(void);
	CFXBlockMathIntLessEqual(CFXBlock*pBlock);
	bool Calc();
	~CFXBlockMathIntLessEqual(void);
	int GetClassID() {
		return BLOCK_MATH_INT_LESSEQUAL;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockMathIntLessEqual");
	}
};

