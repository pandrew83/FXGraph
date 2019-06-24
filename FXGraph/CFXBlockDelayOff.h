﻿#pragma once
#include "FXBlock.h"
class CFXBlockDelayOff :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockDelayOff);
	CFXBlockDelayOff();
	void Create(CFXObject* pObject);
	~CFXBlockDelayOff();
	void Initialize() {
		CFXBlock::Initialize();
		m_Ticks = 0;
	}
	bool Calc();
	int m_Ticks;
};

