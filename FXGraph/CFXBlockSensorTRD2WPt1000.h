#pragma once
#include "FXBlock.h"

class CFXBlockSensorTRD2WPt1000 :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockSensorTRD2WPt1000);
	CFXBlockSensorTRD2WPt1000();
	void Create(CFXObject* pObject);
	bool Calc();
};

