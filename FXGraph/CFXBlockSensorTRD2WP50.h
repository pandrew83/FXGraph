#pragma once
#include "FXBlock.h"

class CFXBlockSensorTRD2WP50 :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockSensorTRD2WP50);
	CFXBlockSensorTRD2WP50();
	CFXBlockSensorTRD2WP50(CFXBlock* pBlock);
	bool Calc();
	int GetClassID() {
		return BLOCK_SENSOR_TRD_2W_P50;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockSensorTRD2WP50");
	}
};

