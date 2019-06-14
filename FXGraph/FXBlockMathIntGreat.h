#pragma once
#include "fxblock.h"
class CFXBlockMathIntGreat :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathIntGreat);
	CFXBlockMathIntGreat(void);
	CFXBlockMathIntGreat(CFXBlock* pBlock);
	bool Calc();
	~CFXBlockMathIntGreat(void);
	int GetClassID() {
		return BLOCK_MATH_INT_GREAT;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockMathIntGreat");
	}
};

