#pragma once
#include "FXBlock.h"

class CFXBlockSensorTRD4WPt500 :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockSensorTRD4WPt500);
	CFXBlockSensorTRD4WPt500();
	void Create(CFXObject* pObject);
	bool Calc();
};

