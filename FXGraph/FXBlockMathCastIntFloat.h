#pragma once
#include "fxblock.h"
class CFXBlockMathCastIntFloat :
	public CFXBlock
{
public:
	CFXBlockMathCastIntFloat(void);
	DECLARE_SERIAL(CFXBlockMathCastIntFloat);
	CFXBlockMathCastIntFloat(CFXBlock*pBlock):CFXBlock(pBlock){
		m_Name = "Int2Float";
		m_MinHeight = m_Height = 50;
		m_PinInMinCount = 1;
		m_PinInMaxCount = 1;
		m_PinOutMinCount = 1;
		m_PinOutMaxCount = 1;
		m_InputPinTypes.AddTail(Int);
		m_OutputPinTypes.AddTail(Float);

		AddInputPin(Int,_T("x"));
		AddOutputPin(Float,_T("z"));
	}
	~CFXBlockMathCastIntFloat(void);
	int GetClassID(){
		return BLOCK_MATH_CAST_INT_FLOAT;
	}
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};

