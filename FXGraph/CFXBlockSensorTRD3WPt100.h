#pragma once
#include "FXBlock.h"

class CFXBlockSensorTRD3WPt100 :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockSensorTRD3WPt100);
	CFXBlockSensorTRD3WPt100();
	CFXBlockSensorTRD3WPt100(CFXBlock* pBlock);
	bool Calc();
};

