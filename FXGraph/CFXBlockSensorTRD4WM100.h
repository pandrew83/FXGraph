#pragma once
#include "FXBlock.h"

class CFXBlockSensorTRD4WM100 :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockSensorTRD4WM100);
	CFXBlockSensorTRD4WM100();
	CFXBlockSensorTRD4WM100(CFXBlock* pBlock);
	bool Calc();
};

