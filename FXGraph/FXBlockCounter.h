#pragma once
#include "fxblock.h"
class CFXBlockCounter :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockCounter);
	CFXBlockCounter(void);
	CFXBlockCounter(CFXBlock* pBlock);
	bool Calc();
	~CFXBlockCounter(void);
	bool Check(void);
	int m_do;
	void Initialize(void);
	int GetClassID() {
		return BLOCK_COUNTER;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockCounter");
	}
};

