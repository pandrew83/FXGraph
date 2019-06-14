#pragma once
#include "FXBlock.h"

class CFXBlockSensorTRD2WP100 :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockSensorTRD2WP100);
	CFXBlockSensorTRD2WP100();
	CFXBlockSensorTRD2WP100(CFXBlock* pBlock);
	bool Calc();
	int GetClassID() {
		return BLOCK_SENSOR_TRD_2W_P100;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockSensorTRD2WP100");
	}
};

