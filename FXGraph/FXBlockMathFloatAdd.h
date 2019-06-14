#pragma once
#include "fxblock.h"
class CFXBlockMathFloatAdd :
	public CFXBlock
{
public:
	CFXBlockMathFloatAdd(void);
	DECLARE_SERIAL(CFXBlockMathFloatAdd);
	CFXBlockMathFloatAdd(CFXBlock* pBlock);
	~CFXBlockMathFloatAdd(void);
	int GetClassID(){
		return BLOCK_MATH_FLOAT_ADD;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockMathFloatAdd");
	}
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};

