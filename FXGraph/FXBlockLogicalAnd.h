#pragma once
#include "fxblock.h"

class CFXBlockLogicalAnd : public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockLogicalAnd)
	CFXBlockLogicalAnd(void);
	void Create(CFXObject* pObject);
	~CFXBlockLogicalAnd(void);
	void Serialize(CArchive& ar){
		CFXBlock::Serialize(ar);
	}
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};

