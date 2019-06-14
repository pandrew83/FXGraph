#pragma once
#include "FXBlock.h"
class CFXBlockSensorTRD2WM100 :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockSensorTRD2WM100);
	CFXBlockSensorTRD2WM100();
	CFXBlockSensorTRD2WM100(CFXBlock* pBlock);
	bool Calc();
	int GetClassID() {
		return BLOCK_SENSOR_TRD_2W_M100;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockSensorTRD2WM100");
	}
};

