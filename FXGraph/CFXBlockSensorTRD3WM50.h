#pragma once
#include "FXBlock.h"

class CFXBlockSensorTRD3WM50 :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockSensorTRD3WM50);
	CFXBlockSensorTRD3WM50();
	void Create(CFXObject* pObject);
	bool Calc();
};

