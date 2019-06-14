#pragma once
#include "FXBlock.h"

class CFXBlockSensorTRD3WPt1000 :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockSensorTRD3WPt1000);
	CFXBlockSensorTRD3WPt1000();
	CFXBlockSensorTRD3WPt1000(CFXBlock* pBlock);
	bool Calc();
	int GetClassID() {
		return BLOCK_SENSOR_TRD_3W_PT1000;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockSensorTRD3WPt1000");
	}
};

