#pragma once
#include "fxblock.h"
class CFXBlockMathFloatSub :
	public CFXBlock
{
public:
	CFXBlockMathFloatSub(void);
	DECLARE_SERIAL(CFXBlockMathFloatSub);
	CFXBlockMathFloatSub(CFXBlock* pBlock);
	~CFXBlockMathFloatSub(void);
	int GetClassID(){
		return BLOCK_MATH_FLOAT_SUB;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockMathFloatSub");
	}
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};

