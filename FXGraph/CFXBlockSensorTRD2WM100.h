#pragma once
#include "FXBlock.h"
class CFXBlockSensorTRD2WM100 :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockSensorTRD2WM100);
	CFXBlockSensorTRD2WM100();
	CFXBlockSensorTRD2WM100(CFXBlock* pBlock);
	bool Calc();
};

