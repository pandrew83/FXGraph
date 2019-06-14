#pragma once
#include "fxblock.h"

class CFXBlockMathBitwiseShiftRight :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathBitwiseShiftRight);
	CFXBlockMathBitwiseShiftRight(void);
	CFXBlockMathBitwiseShiftRight(CFXBlock* pBlock);
	~CFXBlockMathBitwiseShiftRight(void);
	int GetClassID(){
		return BLOCK_MATH_BITWISE_SHIFT_RIGHT;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockMathBitwiseShiftRight");
	}
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};

