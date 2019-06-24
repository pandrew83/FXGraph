#pragma once
#include "FXBlock.h"

class CFXBlockSensorTRD2WPt100 :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockSensorTRD2WPt100);
	CFXBlockSensorTRD2WPt100();
	void Create(CFXObject* pObject);
	bool Calc();
};

