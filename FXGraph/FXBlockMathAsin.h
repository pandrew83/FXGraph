#pragma once
#include "fxblock.h"
class CFXBlockMathAsin :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathAsin);
	CFXBlockMathAsin(void);
	CFXBlockMathAsin(CFXBlock* pBlock);
	bool Calc();
	~CFXBlockMathAsin(void);
	int GetClassID() {
		return BLOCK_MATH_ASIN;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockMathAsin");
	}
};

