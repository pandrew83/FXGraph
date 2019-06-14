#pragma once
#include "FXBlock.h"

class CFXBlockSensorTRD2WPt100 :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockSensorTRD2WPt100);
	CFXBlockSensorTRD2WPt100();
	CFXBlockSensorTRD2WPt100(CFXBlock* pBlock);
	bool Calc();
	int GetClassID() {
		return BLOCK_SENSOR_TRD_2W_PT100;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockSensorTRD2WPt100");
	}
};

