#pragma once
#include "FXBlock.h"

class CFXBlockSensorTRD2WPt500 :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockSensorTRD2WPt500);
	CFXBlockSensorTRD2WPt500();
	CFXBlockSensorTRD2WPt500(CFXBlock* pBlock);
	bool Calc();
};

