#pragma once
#include "FXBlock.h"

class CFXBlockSensorTRD4WPt1000 :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockSensorTRD4WPt1000);
	CFXBlockSensorTRD4WPt1000();
	void Create(CFXObject* pObject);
	bool Calc();
};

