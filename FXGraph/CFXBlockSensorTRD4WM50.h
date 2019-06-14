#pragma once
#include "FXBlock.h"

class CFXBlockSensorTRD4WM50 :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockSensorTRD4WM50);
	CFXBlockSensorTRD4WM50();
	CFXBlockSensorTRD4WM50(CFXBlock* pBlock);
	bool Calc();
	int GetClassID() {
		return BLOCK_SENSOR_TRD_4W_M50;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockSensorTRD4WM50");
	}
};

