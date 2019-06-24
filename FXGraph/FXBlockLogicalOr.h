#pragma once
#include "fxblock.h"
class CFXBlockLogicalOr :
	public CFXBlock
{
public:
	CFXBlockLogicalOr(void);
	DECLARE_SERIAL(CFXBlockLogicalOr);
	void Create(CFXObject* pObject);
	~CFXBlockLogicalOr(void);
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};

