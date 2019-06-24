#pragma once
#include "FXBlock.h"

class CFXBlockSensorTRD3WPt500 :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockSensorTRD3WPt500);
	CFXBlockSensorTRD3WPt500();
	void Create(CFXObject* pObject);
	bool Calc();
};

