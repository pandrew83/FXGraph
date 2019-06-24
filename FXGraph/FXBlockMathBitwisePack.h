#pragma once
#include "fxblock.h"
class CFXBlockMathBitwisePack :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathBitwisePack);
	void Create(CFXObject* pObject);
	CFXBlockMathBitwisePack(void);
	~CFXBlockMathBitwisePack(void);
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};

