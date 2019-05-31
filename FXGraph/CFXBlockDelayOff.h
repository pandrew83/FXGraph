#pragma once
#include "FXBlock.h"
class CFXBlockDelayOff :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockDelayOff);
	CFXBlockDelayOff();
	CFXBlockDelayOff(CFXBlock* pBlock);
	~CFXBlockDelayOff();
	void Initialize() {
		CFXBlock::Initialize();
		m_Ticks = 0;
	}
	bool Calc();
	int m_Ticks;
};

