#pragma once
#include "FXBlock.h"

class CFXBlockSensorTRD4WP100 :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockSensorTRD4WP100);
	CFXBlockSensorTRD4WP100();
	void Create(CFXObject* pObject);
	bool Calc();
};

