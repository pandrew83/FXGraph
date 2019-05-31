#pragma once
#include "FXBlock.h"

class CFXBlockSensorTRD2WPt100 :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockSensorTRD2WPt100);
	CFXBlockSensorTRD2WPt100();
	CFXBlockSensorTRD2WPt100(CFXBlock* pBlock);
	bool Calc();
};

