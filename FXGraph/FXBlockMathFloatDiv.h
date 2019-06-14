#pragma once
#include "fxblock.h"
class CFXBlockMathFloatDiv :
	public CFXBlock
{
public:
	CFXBlockMathFloatDiv(void);
	DECLARE_SERIAL(CFXBlockMathFloatDiv);
	CFXBlockMathFloatDiv(CFXBlock* pBlock);
	~CFXBlockMathFloatDiv(void);
	int GetClassID(){
		return BLOCK_MATH_FLOAT_DIV;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockMathFloatDiv");
	}
	bool Calc(void);
};

