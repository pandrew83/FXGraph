#pragma once
#include "FXBlock.h"

class CFXBlockSensorTRD3WPt500 :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockSensorTRD3WPt500);
	CFXBlockSensorTRD3WPt500();
	CFXBlockSensorTRD3WPt500(CFXBlock* pBlock);
	bool Calc();
	int GetClassID() {
		return BLOCK_SENSOR_TRD_3W_PT500;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockSensorTRD3WPt500");
	}
};

