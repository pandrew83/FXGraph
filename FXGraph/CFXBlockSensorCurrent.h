#pragma once
#include "FXBlock.h"
class CFXBlockSensorCurrent :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockSensorCurrent);
	CFXBlockSensorCurrent();
	CFXBlockSensorCurrent(CFXBlock* pBlock);
	bool Calc();

};

