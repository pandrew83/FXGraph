#pragma once
#include "FXBlock.h"
class CFXBlockTransformLinear :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockTransformLinear);
	CFXBlockTransformLinear();
	void Create(CFXObject* pObject);
	bool Calc();
};

