#pragma once
#include "FXBlock.h"
class CFXBlockMemoryFloat :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMemoryFloat);
	CFXBlockMemoryFloat();
	~CFXBlockMemoryFloat();
	bool Calc();
	void Create(CFXObject* pObject);
	void Initialize();
protected:
	double m_Memory;
};

