#pragma once
#include "FXBlock.h"
class CFXBlockTransformLinearLimits :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockTransformLinearLimits);
	CFXBlockTransformLinearLimits();
	void Create(CFXObject* pObject);
	bool Calc();
};

