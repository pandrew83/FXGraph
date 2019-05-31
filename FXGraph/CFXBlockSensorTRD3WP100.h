#pragma once
#include "FXBlock.h"

class CFXBlockSensorTRD3WP100 :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockSensorTRD3WP100);
	CFXBlockSensorTRD3WP100();
	CFXBlockSensorTRD3WP100(CFXBlock* pBlock);
	bool Calc();
};

