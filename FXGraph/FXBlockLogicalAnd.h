#pragma once
#include "fxblock.h"

class CFXBlockLogicalAnd : public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockLogicalAnd)
	CFXBlockLogicalAnd(void);
	CFXBlockLogicalAnd(CFXBlock* pBlock);
	int GetClassID(){
		return BLOCK_LOGICAL_AND;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockLogicalAnd");
	}
	~CFXBlockLogicalAnd(void);
	void Serialize(CArchive& ar){
		CFXBlock::Serialize(ar);
	}
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};

