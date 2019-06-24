#pragma once
#include "fxblock.h"
class CFXBlockLogicalNot :
	public CFXBlock
{
public:
	CFXBlockLogicalNot(void);
	DECLARE_SERIAL(CFXBlockLogicalNot);
	void Create(CFXObject* pObject);
	~CFXBlockLogicalNot(void);
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};

