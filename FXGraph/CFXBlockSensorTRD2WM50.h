﻿#pragma once
#include "FXBlock.h"

class CFXBlockSensorTRD2WM50 :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockSensorTRD2WM50);
	CFXBlockSensorTRD2WM50();
	void Create(CFXObject* pObject);
	bool Calc();
};

