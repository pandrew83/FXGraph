#pragma once
#include "FXBlock.h"

class CFXBlockSensorTRD3WM100 :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockSensorTRD3WM100);
	CFXBlockSensorTRD3WM100();
	CFXBlockSensorTRD3WM100(CFXBlock* pBlock);
	bool Calc();
};

