#pragma once
#include "FXBlock.h"

class CFXBlockSensorTRD3WPt1000 :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockSensorTRD3WPt1000);
	CFXBlockSensorTRD3WPt1000();
	CFXBlockSensorTRD3WPt1000(CFXBlock* pBlock);
	bool Calc();
};

