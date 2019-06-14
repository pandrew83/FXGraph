#pragma once
#include "fxblock.h"
class CFXBlockMathLog :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathLog);
	CFXBlockMathLog(void);
	CFXBlockMathLog(CFXBlock* pBlock);
	bool Calc();
	~CFXBlockMathLog(void);
	int GetClassID() {
		return BLOCK_MATH_LOG;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockMathLog");
	}
};

