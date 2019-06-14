#pragma once
#include "fxblock.h"
class CFXBlockMathFloatFloor :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathFloatFloor);
	CFXBlockMathFloatFloor(void);
	CFXBlockMathFloatFloor(CFXBlock* pBlock);
	bool Calc();
	~CFXBlockMathFloatFloor(void);
	int GetClassID() {
		return BLOCK_MATH_FLOAT_FLOOR;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockMathFloatFloor");
	}
};

