#pragma once
#include "FXBlock.h"
class CFXBlockAntiBounce :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockAntiBounce);
	CFXBlockAntiBounce();
	void Create(CFXObject* pObject);
	~CFXBlockAntiBounce();
	bool Calc();
	void Initialize() {
		CFXBlock::Initialize();
		m_Ticks = 0;
	}

public:
	int m_Ticks;
};

