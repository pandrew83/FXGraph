#pragma once
#include "FXBlock.h"

class CFXBlockSensorTRD3WP50 :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockSensorTRD3WP50);
	CFXBlockSensorTRD3WP50();
	void Create(CFXObject* pObject);
	bool Calc();
};

