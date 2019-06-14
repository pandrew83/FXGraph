#pragma once
#include "FXBlock.h"

class CFXBlockSensorTRD4WPt100 :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockSensorTRD4WPt100);
	CFXBlockSensorTRD4WPt100();
	CFXBlockSensorTRD4WPt100(CFXBlock* pBlock);
	bool Calc();
	int GetClassID() {
		return BLOCK_SENSOR_TRD_4W_PT100;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockSensorTRD4WPt100");
	}
};

