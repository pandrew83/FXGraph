#pragma once
#include "FXBlock.h"
class CFXBlockAntiBounce :
	public CFXBlock
{
	DECLARE_SERIAL(CFXBlockAntiBounce);
	CFXBlockAntiBounce();
	CFXBlockAntiBounce(CFXBlock* pBlock);
	~CFXBlockAntiBounce();
	int GetClassID() {
		return BLOCK_ANTIBOUNCE;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockAntiBounce");
	}
	bool Calc();
	void Initialize() {
		CFXBlock::Initialize();
		m_Ticks = 0;
	}

public:
	int m_Ticks;
};

