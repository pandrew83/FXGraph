#pragma once
#include "FXBlock.h"
class CFXBlockMemoryInt :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMemoryInt);
	CFXBlockMemoryInt();
	~CFXBlockMemoryInt();
	bool Calc();
	void Initialize();
	void Create(CFXObject* pObject);
protected:
	int m_Memory;
};

