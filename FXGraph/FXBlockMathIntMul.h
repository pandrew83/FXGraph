#pragma once
#include "fxblock.h"
class CFXBlockMathIntMul :
	public CFXBlock
{
public:
	CFXBlockMathIntMul(void);
	DECLARE_SERIAL(CFXBlockMathIntMul);
	CFXBlockMathIntMul(CFXBlock* pBlock);
	~CFXBlockMathIntMul(void);
	int GetClassID(){
		return BLOCK_MATH_INT_MUL;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockMathIntMul");
	}
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};

