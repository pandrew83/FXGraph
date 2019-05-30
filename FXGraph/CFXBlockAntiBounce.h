#pragma once
#include "FXBlock.h"
class CFXBlockAntiBounce :
	public CFXBlock
{
	CFXBlockAntiBounce();
	CFXBlockAntiBounce(CFXBlock* pBlock);
	~CFXBlockAntiBounce();
	bool Calc();


public:
	int m_Ticks;
};

