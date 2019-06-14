#pragma once
#include "FXBlock.h"

class CFXBlockSensorTRD3WP100 :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockSensorTRD3WP100);
	CFXBlockSensorTRD3WP100();
	CFXBlockSensorTRD3WP100(CFXBlock* pBlock);
	bool Calc();
	int GetClassID() {
		return BLOCK_SENSOR_TRD_3W_P100;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockSensorTRD3WP100");
	}
};

