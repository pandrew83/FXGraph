#pragma once
#include "FXBlock.h"

class CFXBlockSensorTRD2WP50 :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockSensorTRD2WP50);
	CFXBlockSensorTRD2WP50();
	void Create(CFXObject* pObject);
	bool Calc();
};

