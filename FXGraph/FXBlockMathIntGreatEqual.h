#pragma once
#include "fxblock.h"
class CFXBlockMathIntGreatEqual :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathIntGreatEqual);
	CFXBlockMathIntGreatEqual(void);
	CFXBlockMathIntGreatEqual(CFXBlock* pBlock);
	bool Calc();
	~CFXBlockMathIntGreatEqual(void);
	int GetClassID() {
		return BLOCK_MATH_INT_GREATEQUAL;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockMathIntGreatEqual");
	}
};

