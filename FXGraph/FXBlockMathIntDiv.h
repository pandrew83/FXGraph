#pragma once
#include "fxblock.h"
class CFXBlockMathIntDiv :
	public CFXBlock
{
public:
	CFXBlockMathIntDiv(void);
	DECLARE_SERIAL(CFXBlockMathIntDiv);
	CFXBlockMathIntDiv(CFXBlock* pBlock);
	~CFXBlockMathIntDiv(void);
	int GetClassID(){
		return BLOCK_MATH_INT_DIV;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockMathIntDiv");
	}
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};

