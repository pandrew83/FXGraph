#pragma once
#include "FXBlock.h"

class CFXBlockMathBitwiseShiftLeft : public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathBitwiseShiftLeft);
	CFXBlockMathBitwiseShiftLeft(void);
	CFXBlockMathBitwiseShiftLeft(CFXBlock* pBlock);
	~CFXBlockMathBitwiseShiftLeft(void);
	int GetClassID(){
		return BLOCK_MATH_BITWISE_SHIFT_LEFT;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockMathBitwiseShiftLeft");
	}
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};

