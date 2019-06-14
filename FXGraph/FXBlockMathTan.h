#pragma once
#include "fxblock.h"
class CFXBlockMathTan :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathTan);
	CFXBlockMathTan(void);
	CFXBlockMathTan(CFXBlock* pBlock);
	bool Calc();
	~CFXBlockMathTan(void);
	int GetClassID() {
		return BLOCK_MATH_TAN;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockMathTan");
	}
};

