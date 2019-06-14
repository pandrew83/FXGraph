#pragma once
#include "fxblock.h"
class CFXBlockMathBitwiseXor :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathBitwiseXor);
	CFXBlockMathBitwiseXor(void);
	CFXBlockMathBitwiseXor(CFXBlock* pBlock);
	~CFXBlockMathBitwiseXor(void);
	int GetClassID(){
		return BLOCK_MATH_BITWISE_XOR;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockMathBitwiseXor");
	}
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};

