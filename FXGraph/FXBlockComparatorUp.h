#pragma once
#include "fxblock.h"
class CFXBlockComparatorUp :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockComparatorUp);
	CFXBlockComparatorUp(void);
	void Create(CFXObject* pObject);
	bool Calc();
	~CFXBlockComparatorUp(void);
	bool m_Prev;
	void Initialize(void);
	int GetClassID() {
		return BLOCK_COMPARATOR_UP;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockComparatorUp");
	}
};

