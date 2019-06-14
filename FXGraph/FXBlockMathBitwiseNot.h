#pragma once
#include "fxblock.h"
class CFXBlockMathBitwiseNot :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathBitwiseNot);
	CFXBlockMathBitwiseNot(void);
	CFXBlockMathBitwiseNot(CFXBlock* pBlock);
	~CFXBlockMathBitwiseNot(void);
	int GetClassID(){
		return BLOCK_MATH_BITWISE_NOT;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockMathBitwiseNot");
	}
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};

