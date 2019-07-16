#pragma once
#include "FXBlock.h"
class CFXBlockPID :
	public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockPID);
	CFXBlockPID();
	~CFXBlockPID();
//	void Create(
	void Create(CFXObject* pObject);
	bool Calc();
	void Initialize();
protected:
	double m_i;
	int m_Ticks;
	double m_LastError;
};

