#pragma once
#include "fxblock.h"
class CFXBlockMathFloatSub :
	public CFXBlock
{
public:
	CFXBlockMathFloatSub(void);
	DECLARE_SERIAL(CFXBlockMathFloatSub);
	CFXBlockMathFloatSub(CFXBlock* pBlock):CFXBlock(pBlock){
		m_Name = "X - Y";
		m_PinInMinCount = 2;
		m_PinInMaxCount = 2;
		m_PinOutMinCount = 1;
		m_PinOutMaxCount = 1;
		m_InputPinTypes.AddTail(Float);
		m_OutputPinTypes.AddTail(Float);
		AddInputPin(Float,_T("x"));
		AddInputPin(Float,_T("y"));
		AddOutputPin(Float,_T("z"));
	}
	~CFXBlockMathFloatSub(void);
	int GetClassID(){
		return BLOCK_MATH_FLOAT_SUB;
	}
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};

