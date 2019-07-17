#pragma once
#include "FXBlock.h"
class CFXBlockMathFloatLimits :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockMathFloatLimits);
	CFXBlockMathFloatLimits();
	~CFXBlockMathFloatLimits();
	void Create(CFXObject* pObject);
	bool Calc();
	void Initialize();
protected:
	double m_Current;
};

