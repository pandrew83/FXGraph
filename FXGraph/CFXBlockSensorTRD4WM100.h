#pragma once
#include "FXBlock.h"

class CFXBlockSensorTRD4WM100 :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockSensorTRD4WM100);
	CFXBlockSensorTRD4WM100();
	CFXBlockSensorTRD4WM100(CFXBlock* pBlock);
	bool Calc();
	int GetClassID() {
		return BLOCK_SENSOR_TRD_4W_M100;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockSensorTRD4WM100");
	}
};

