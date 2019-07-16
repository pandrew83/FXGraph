#pragma once
#include "FXBlock.h"
class CFXBlockSetupBool :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockSetupBool);
	CFXBlockSetupBool();
	~CFXBlockSetupBool();
	void Initialize();
	void Create(CFXObject* pObject);
	bool Calc();
};

