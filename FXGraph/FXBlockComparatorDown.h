#pragma once
#include "fxblock.h"
class CFXBlockComparatorDown :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockComparatorDown);
	CFXBlockComparatorDown(void);
	CFXBlockComparatorDown(CFXBlock*pBlock);
	~CFXBlockComparatorDown(void);
	bool Calc();
	bool m_Prev;
	void Initialize(void);
	int GetClassID() {
		return BLOCK_COMPARATOR_DOWN;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockComparatorDown");
	}
};

