#pragma once
#include "fxblock.h"
class CFXBlockMathCastFloatInt :
	public CFXBlock
{
public:
	CFXBlockMathCastFloatInt(void);
	DECLARE_SERIAL(CFXBlockMathCastFloatInt);
	CFXBlockMathCastFloatInt(CFXBlock*pBlock):CFXBlock(pBlock){
		m_Name = "Float2Int";
		m_MinHeight = m_Height = 50;
		m_PinInMinCount = 1;
		m_PinInMaxCount = 1;
		m_PinOutMinCount = 1;
		m_PinOutMaxCount = 1;
		m_InputPinTypes.AddTail(Float);
		m_OutputPinTypes.AddTail(Int);

		AddInputPin(Float,_T("x"));
		AddOutputPin(Int,_T("z"));
	}
	~CFXBlockMathCastFloatInt(void);
	int GetClassID(){
		return BLOCK_MATH_CAST_FLOAT_INT;
	}
	virtual bool Check(){
		return CFXBlock::Check();
	}
	bool Calc(void);
};

