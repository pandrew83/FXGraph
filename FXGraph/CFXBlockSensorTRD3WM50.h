#pragma once
#include "FXBlock.h"

class CFXBlockSensorTRD3WM50 :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockSensorTRD3WM50);
	CFXBlockSensorTRD3WM50();
	CFXBlockSensorTRD3WM50(CFXBlock* pBlock);
	bool Calc();
	int GetClassID() {
		return BLOCK_SENSOR_TRD_3W_M50;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockSensorTRD3WM50");
	}
};

