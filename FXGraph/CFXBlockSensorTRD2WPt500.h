#pragma once
#include "FXBlock.h"

class CFXBlockSensorTRD2WPt500 :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockSensorTRD2WPt500);
	CFXBlockSensorTRD2WPt500();
	CFXBlockSensorTRD2WPt500(CFXBlock* pBlock);
	bool Calc();
	int GetClassID() {
		return BLOCK_SENSOR_TRD_2W_PT500;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockSensorTRD2WPt500");
	}
};

