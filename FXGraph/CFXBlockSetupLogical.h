#pragma once
#include "FXBlock.h"
class CFXBlockSetupLogical :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockSetupLogical);
	CFXBlockSetupLogical();
	~CFXBlockSetupLogical();
	void Initialize();
	void Create(CFXObject* pObject);
	bool Calc();
};

