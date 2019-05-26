#pragma once
#include "fxblock.h"
class CFXBlockMathFloatAdd :
	public CFXBlock
{
public:
	CFXBlockMathFloatAdd(void);
	DECLARE_SERIAL(CFXBlockMathFloatAdd);
	CFXBlockMathFloatAdd(CFXBlock* pBlock):CFXBlock(pBlock){
		m_Name = "X + Y";
		m_PinInMaxCount = 32;
		m_PinInMinCount = 2;
		m_PinOutMinCount = 1;
		m_PinOutMaxCount = 1;
		m_InputPinTypes.AddTail(Float);
		m_OutputPinTypes.AddTail(Float);
		AddInputPin(Float,_T("x"));
		AddInputPin(Float,_T("y"));
		AddOutputPin(Float,_T("z"));
	}
	~CFXBlockMathFloatAdd(void);
	int GetClassID(){
		return BLOCK_MATH_FLOAT_ADD;
	}
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};

