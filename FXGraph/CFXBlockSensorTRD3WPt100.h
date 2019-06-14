#pragma once
#include "FXBlock.h"

class CFXBlockSensorTRD3WPt100 :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockSensorTRD3WPt100);
	CFXBlockSensorTRD3WPt100();
	CFXBlockSensorTRD3WPt100(CFXBlock* pBlock);
	bool Calc();
	int GetClassID() {
		return BLOCK_SENSOR_TRD_3W_PT100;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockSensorTRD3WPt100");
	}
};

