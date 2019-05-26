#pragma once
#include "fxblock.h"
class CFXBlockMathFloatDiv :
	public CFXBlock
{
public:
	CFXBlockMathFloatDiv(void);
	DECLARE_SERIAL(CFXBlockMathFloatDiv);
	CFXBlockMathFloatDiv(CFXBlock* pBlock):CFXBlock(pBlock){
		m_Name = "X / Y";
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
	~CFXBlockMathFloatDiv(void);
	int GetClassID(){
		return BLOCK_MATH_FLOAT_DIV;
	}
	bool Calc(void);
};

