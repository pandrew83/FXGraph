#pragma once
#include "fxblock.h"
class CFXBlockLogicalRisingEdge :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockLogicalRisingEdge);
	CFXBlockLogicalRisingEdge(void);
	CFXBlockLogicalRisingEdge(CFXBlock* pBlock);
	~CFXBlockLogicalRisingEdge(void);
	bool Calc();
	bool m_Prev;
	void Initialize(void);
	int GetClassID() {
		return BLOCK_LOGICAL_RISING_EDGE;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockLogicalRisingEdge");
	}
};

