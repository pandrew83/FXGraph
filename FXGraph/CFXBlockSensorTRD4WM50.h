﻿#pragma once
#include "FXBlock.h"

class CFXBlockSensorTRD4WM50 :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockSensorTRD4WM50);
	CFXBlockSensorTRD4WM50();
	void Create(CFXObject* pObject);
	bool Calc();
};

