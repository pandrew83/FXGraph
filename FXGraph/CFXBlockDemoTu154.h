#pragma once
#include "FXBlock.h"
class CFXBlockDemoTu154 :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockDemoTu154);
	CFXBlockDemoTu154();
	~CFXBlockDemoTu154();
	void Create(CFXObject* pObject);
	bool Calc();
	void Initialize();

};

