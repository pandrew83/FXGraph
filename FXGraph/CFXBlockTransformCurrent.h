#pragma once
#include "FXBlock.h"
class CFXBlockTransformCurrent :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockTransformCurrent);
	CFXBlockTransformCurrent();
	CFXBlockTransformCurrent(CFXBlock* pBlock);
	bool Calc();

};

