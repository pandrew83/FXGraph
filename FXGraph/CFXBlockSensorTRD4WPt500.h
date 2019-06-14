#pragma once
#include "FXBlock.h"

class CFXBlockSensorTRD4WPt500 :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockSensorTRD4WPt500);
	CFXBlockSensorTRD4WPt500();
	CFXBlockSensorTRD4WPt500(CFXBlock* pBlock);
	bool Calc();
	int GetClassID() {
		return BLOCK_SENSOR_TRD_4W_PT500;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockSensorTRD4WPt500");
	}
};

