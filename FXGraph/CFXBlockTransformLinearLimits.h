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
	int GetClassID() {
		return BLOCK_TRANSFORM_LINEAR_LIMITS;
	}
	CString GetClassDescription() {
		return _T("CFXBlockTransformLinearLimits");
	}
};

