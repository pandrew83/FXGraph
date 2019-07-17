#pragma once
#include "FXBlock.h"
class CFXBlockMemoryLogical :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMemoryLogical);
	CFXBlockMemoryLogical();
	~CFXBlockMemoryLogical();
	bool Calc();
	void Initialize();
	void Create(CFXObject* pObject);
protected:
	bool m_Memory;
};

