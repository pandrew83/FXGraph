#pragma once
#include "FXBlock.h"
class CFXBlockTransformLinear :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockTransformLinear);
	CFXBlockTransformLinear();
	CFXBlockTransformLinear(CFXBlock* pBlock);
	bool Calc();
};

