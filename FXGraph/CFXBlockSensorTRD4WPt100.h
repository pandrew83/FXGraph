#pragma once
#include "FXBlock.h"

class CFXBlockSensorTRD4WPt100 :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockSensorTRD4WPt100);
	CFXBlockSensorTRD4WPt100();
	CFXBlockSensorTRD4WPt100(CFXBlock* pBlock);
	bool Calc();
};

