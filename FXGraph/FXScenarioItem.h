#pragma once
class CFXObject;
class CFXPin;
#include "./cparse/shunting-yard.h"

class CFXScenarioItem
{
public:
	CFXScenarioItem(void);
	~CFXScenarioItem(void);
	CString m_Condition;
	CString m_Expression;
	CFXPin* m_pPin;
	bool EvalCondition(cparser::TokenMap& vars);
	bool EvalExpression(cparser::TokenMap& vars);
};

