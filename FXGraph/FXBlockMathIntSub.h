#pragma once
#include "fxblock.h"
class CFXBlockMathIntSub :
	public CFXBlock
{
public:
	CFXBlockMathIntSub(void);
	DECLARE_SERIAL(CFXBlockMathIntSub);
	CFXBlockMathIntSub(CFXBlock* pBlock);
	~CFXBlockMathIntSub(void);
	int GetClassID(){
		return BLOCK_MATH_INT_SUB;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockMathIntSub");
	}
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
	
};

