#pragma once
#include "fxblock.h"
class CFXBlockMathBitwisePack :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathBitwisePack);
	CFXBlockMathBitwisePack(CFXBlock* pBlock);
	CFXBlockMathBitwisePack(void);
	~CFXBlockMathBitwisePack(void);
	int GetClassID(){
		return BLOCK_MATH_BITWISE_PACK;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockMathBitwisePack");
	}
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};

