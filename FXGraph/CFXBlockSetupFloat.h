#pragma once
#include "FXBlock.h"
class CFXBlockSetupFloat :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockSetupFloat);
	CFXBlockSetupFloat();
	~CFXBlockSetupFloat();
	void Initialize();
	void Create(CFXObject* pObject);
	bool Calc();
};

