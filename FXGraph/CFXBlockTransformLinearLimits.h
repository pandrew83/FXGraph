#pragma once
#include "FXBlock.h"
class CFXBlockTransformLinearLimits :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockTransformLinearLimits);
	CFXBlockTransformLinearLimits();
	CFXBlockTransformLinearLimits(CFXBlock* pBlock);
	bool Calc();
};

