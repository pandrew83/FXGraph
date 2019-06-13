#pragma once
#include "fxblockfunctional.h"

class CFXBlockController :
	public CFXBlockFunctional
{
public:
	DECLARE_SERIAL(CFXBlockController);
	CFXBlockController(void);
	CFXBlockController(CFXBlock* pBlock);
	~CFXBlockController(void);
protected:
	int m_Ticks;
	int m_TicksPerSec;
public:
	virtual void FillProperties(CPropertiesWnd* pWnd);
};

