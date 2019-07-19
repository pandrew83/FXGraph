#pragma once
#include "fxblockfunctional.h"

class CFXBlockController :
	public CFXBlockFunctional
{
public:
	DECLARE_SERIAL(CFXBlockController);
	CFXBlockController(void);
	~CFXBlockController(void);
	void Create(CFXObject* pObject);
	virtual bool SetProperty(int nProperty, variant_t& value, CFXGraphView* pView);
protected:
	int m_Ticks;
	int m_TicksPerSec;
public:
	virtual void FillProperties(CPropertiesWnd* pWnd);
};

