#pragma once
#include "fxblock.h"
class CFXBlockLogicalFallingEdge :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockLogicalFallingEdge);
	CFXBlockLogicalFallingEdge(void);
	CFXBlockLogicalFallingEdge(CFXBlock* pBlock);
	bool Calc();
	bool m_Prev;
	~CFXBlockLogicalFallingEdge(void);
	void Initialize(void);
	int GetClassID() {
		return BLOCK_LOGICAL_FALLING_EDGE;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockLogicalFallingEdge");
	}
};

