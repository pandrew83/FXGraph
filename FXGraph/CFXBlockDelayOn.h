#pragma once
#include "FXBlock.h"
class CFXBlockDelayOn :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockDelayOn);
	CFXBlockDelayOn();
	void Create(CFXObject* pObject);
	~CFXBlockDelayOn();
	void Initialize() {
		CFXBlock::Initialize();
		m_Ticks = 0;
	}
	bool Calc();
	int m_Ticks;
	int GetClassID() {
		return BLOCK_DELAY_ON;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockDelayOn");
	}
};

