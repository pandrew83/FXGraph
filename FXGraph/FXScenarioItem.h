#pragma once
class CFXObject;

class CFXScenarioItem
{
public:
	CFXScenarioItem(void);
	~CFXScenarioItem(void);
	CString m_Condition;
	CString m_Expression;
	CFXObject* m_pObject;
	bool EvalCondition();
	bool EvalExpression();
};

