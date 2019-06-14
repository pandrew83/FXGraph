#pragma once
#include "FXBlock.h"

class CFXBlockSensorTRD4WPt1000 :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockSensorTRD4WPt1000);
	CFXBlockSensorTRD4WPt1000();
	CFXBlockSensorTRD4WPt1000(CFXBlock* pBlock);
	bool Calc();
	int GetClassID() {
		return BLOCK_SENSOR_TRD_4W_PT1000;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockSensorTRD4WPt1000");
	}
};

