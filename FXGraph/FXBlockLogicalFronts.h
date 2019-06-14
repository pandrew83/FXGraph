#pragma once
#include "fxblock.h"
class CFXBlockLogicalFronts :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockLogicalFronts);
	CFXBlockLogicalFronts(CFXBlock* pBlock);
	bool Calc();
	CFXBlockLogicalFronts(void);
	~CFXBlockLogicalFronts(void);
	bool m_Prev;
	void Initialize(void);
	int GetClassID() {
		return BLOCK_LOGICAL_FRONTS;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockLogicalFronts");
	}
};

