#pragma once
#include "FXBlock.h"

class CFXBlockSensorTRD4WP100 :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockSensorTRD4WP100);
	CFXBlockSensorTRD4WP100();
	CFXBlockSensorTRD4WP100(CFXBlock* pBlock);
	bool Calc();
	int GetClassID() {
		return BLOCK_SENSOR_TRD_4W_P100;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockSensorTRD4WP100");
	}
};

