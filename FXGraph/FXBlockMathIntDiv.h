#pragma once
#include "fxblock.h"
class CFXBlockMathIntDiv :
	public CFXBlock
{
public:
	CFXBlockMathIntDiv(void);
	DECLARE_SERIAL(CFXBlockMathIntDiv);
	CFXBlockMathIntDiv(CFXBlock* pBlock):CFXBlock(pBlock){
		m_Name = "X / Y";
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
	~CFXBlockMathIntDiv(void);
	int GetClassID(){
		return BLOCK_MATH_INT_DIV;
	}
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};

