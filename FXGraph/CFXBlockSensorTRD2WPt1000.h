#pragma once
#include "FXBlock.h"

class CFXBlockSensorTRD2WPt1000 :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockSensorTRD2WPt1000);
	CFXBlockSensorTRD2WPt1000();
	CFXBlockSensorTRD2WPt1000(CFXBlock* pBlock);
	bool Calc();
	int GetClassID() {
		return BLOCK_SENSOR_TRD_2W_PT1000;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockSensorTRD2WPt1000");
	}
};

