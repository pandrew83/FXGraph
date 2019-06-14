#pragma once
#include "fxblock.h"
class CFXBlockLogicalXor :
	public CFXBlock
{
public:
	CFXBlockLogicalXor(void);
	DECLARE_SERIAL(CFXBlockLogicalXor);
	CFXBlockLogicalXor(CFXBlock* pBlock);
	~CFXBlockLogicalXor(void);
	int GetClassID(){
		return BLOCK_LOGICAL_XOR;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockLogicalXor");
	}
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};

