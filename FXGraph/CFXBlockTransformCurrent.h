#pragma once
#include "FXBlock.h"
class CFXBlockTransformCurrent :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockTransformCurrent);
	CFXBlockTransformCurrent();
	CFXBlockTransformCurrent(CFXBlock* pBlock);
	bool Calc();
	int GetClassID() {
		return BLOCK_TRANSFORM_CURRENT;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockTransformCurrent");
	}
};

