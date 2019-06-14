#pragma once
#include "FXBlock.h"

class CFXBlockSensorTRD3WP50 :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockSensorTRD3WP50);
	CFXBlockSensorTRD3WP50();
	CFXBlockSensorTRD3WP50(CFXBlock* pBlock);
	bool Calc();
	int GetClassID() {
		return BLOCK_SENSOR_TRD_3W_P50;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockSensorTRD3WP50");
	}
};

