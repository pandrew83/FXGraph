#pragma once
#include "fxblock.h"
class CFXBlockMathIntMul :
	public CFXBlock
{
public:
	CFXBlockMathIntMul(void);
	DECLARE_SERIAL(CFXBlockMathIntMul);
	CFXBlockMathIntMul(CFXBlock* pBlock):CFXBlock(pBlock){
		m_Name = "Mul";
		m_PinInMinCount = 2;
		m_PinInMaxCount = 32;
		m_PinOutMinCount = 1;
		m_PinOutMaxCount = 1;
		m_InputPinTypes.AddTail(Int);
		m_OutputPinTypes.AddTail(Int);
		AddInputPin(Int,_T("x"));
		AddInputPin(Int,_T("y"));
		AddOutputPin(Int,_T("z"));
	}
	~CFXBlockMathIntMul(void);
	int GetClassID(){
		return BLOCK_MATH_INT_MUL;
	}
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};

