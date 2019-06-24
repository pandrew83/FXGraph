#pragma once
#include "fxblock.h"
class CFXBlockLogicalXor :
	public CFXBlock
{
public:
	CFXBlockLogicalXor(void);
	DECLARE_SERIAL(CFXBlockLogicalXor);
	void Create(CFXObject* pObject);
	~CFXBlockLogicalXor(void);
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};

