#pragma once
#include "fxblock.h"
class CFXBlockMathCos :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathCos);
	CFXBlockMathCos(void);
	CFXBlockMathCos(CFXBlock* pBlock);
	bool Calc();
	~CFXBlockMathCos(void);
	int GetClassID() {
		return BLOCK_MATH_COS;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockMathCos");
	}
};

