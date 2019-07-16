#pragma once
#include "FXBlock.h"
class CFXBlockSetupInt :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockSetupInt);
	CFXBlockSetupInt();
	~CFXBlockSetupInt();
	void Initialize();
	void Create(CFXObject* pObject);
	bool Calc();
};

