#pragma once
#include "FXBlock.h"

class CFXBlockSensorTRD2WP100 :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockSensorTRD2WP100);
	CFXBlockSensorTRD2WP100();
	CFXBlockSensorTRD2WP100(CFXBlock* pBlock);
	bool Calc();
};

