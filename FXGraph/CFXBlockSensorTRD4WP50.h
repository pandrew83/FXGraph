#pragma once
#include "FXBlock.h"

class CFXBlockSensorTRD4WP50 :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockSensorTRD4WP50);
	CFXBlockSensorTRD4WP50();
	CFXBlockSensorTRD4WP50(CFXBlock* pBlock);
	bool Calc();
};

