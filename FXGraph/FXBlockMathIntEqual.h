#pragma once
#include "fxblock.h"
class CFXBlockMathIntEqual :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathIntEqual);
	CFXBlockMathIntEqual(void);
	CFXBlockMathIntEqual(CFXBlock* pBlock);
	bool Calc();
	int GetClassID() {
		return BLOCK_MATH_INT_EQUAL;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockMathIntEqual");
	}
	~CFXBlockMathIntEqual(void);
};

