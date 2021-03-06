﻿#pragma once
#include "fxblock.h"
class CFXBlockFunctionalPin : public CFXBlock
{
public:
	CFXBlockFunctionalPin(void);
	DECLARE_SERIAL(CFXBlockFunctionalPin)
	CFXBlockFunctionalPin(CFXBlock* pBlock,CFXPin* pLinkedPin);
	~CFXBlockFunctionalPin(void);
	virtual bool Check(){
		return CFXBlock::Check();
	}
	CFXPin* m_pLinkedPin;
	bool Calc(void);
	void Serialize(CArchive& ar);
	virtual void AfterSerialize(void);
	virtual bool IsRemovable();
};

