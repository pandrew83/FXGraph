#pragma once
#include "FXBlock.h"

class CFXBlockSensorTRD3WM100 :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockSensorTRD3WM100);
	CFXBlockSensorTRD3WM100();
	CFXBlockSensorTRD3WM100(CFXBlock* pBlock);
	bool Calc();
	int GetClassID() {
		return BLOCK_SENSOR_TRD_3W_M100;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockSensorTRD3WM100");
	}
};

