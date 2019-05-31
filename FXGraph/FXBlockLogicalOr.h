#pragma once
#include "fxblock.h"
class CFXBlockLogicalOr :
	public CFXBlock
{
public:
	CFXBlockLogicalOr(void);
	DECLARE_SERIAL(CFXBlockLogicalOr);
	CFXBlockLogicalOr(CFXBlock* pBlock);
	~CFXBlockLogicalOr(void);
	int GetClassID(){
		return BLOCK_LOGICAL_OR;
	}
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};
