#pragma once
#include "FXBlock.h"
class CFXBlockTransformCurrent :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockTransformCurrent);
	CFXBlockTransformCurrent();
	void Create(CFXObject* pObject);
	bool Calc();
};

