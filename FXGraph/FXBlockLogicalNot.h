#pragma once
#include "fxblock.h"
class CFXBlockLogicalNot :
	public CFXBlock
{
public:
	CFXBlockLogicalNot(void);
	DECLARE_SERIAL(CFXBlockLogicalNot);
	CFXBlockLogicalNot(CFXBlock* pBlock);
	~CFXBlockLogicalNot(void);
	int GetClassID(){
		return BLOCK_LOGICAL_NOT;
	}
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};
