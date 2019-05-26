#pragma once
#include "fxblock.h"
class CFXBlockComparatorUp :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockComparatorUp);
	CFXBlockComparatorUp(void);
	CFXBlockComparatorUp(CFXBlock* pBlock);
	bool Calc();
	~CFXBlockComparatorUp(void);
	bool m_Prev;
	void Initialize(void);
};

