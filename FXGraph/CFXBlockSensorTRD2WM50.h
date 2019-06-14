#pragma once
#include "FXBlock.h"

class CFXBlockSensorTRD2WM50 :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockSensorTRD2WM50);
	CFXBlockSensorTRD2WM50();
	CFXBlockSensorTRD2WM50(CFXBlock* pBlock);
	bool Calc();
	int GetClassID() {
		return BLOCK_SENSOR_TRD_2W_M50;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockSensorTRD2WM50");
	}
};

