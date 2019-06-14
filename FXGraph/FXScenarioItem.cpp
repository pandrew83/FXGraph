#include "StdAfx.h"
#include "FXScenarioItem.h"
#include "FXPin.h"

CFXScenarioItem::CFXScenarioItem(void)
{
}


CFXScenarioItem::~CFXScenarioItem(void)
{
}

bool CFXScenarioItem::EvalCondition(cparser::TokenMap& vars) {
	CStringA s = CW2A(m_Condition.GetBuffer());
	cparser::packToken token = cparser::calculator::calculate(s, vars);
	return token.asBool();
}

bool CFXScenarioItem::EvalExpression(cparser::TokenMap&vars) {
	CStringA s = CW2A(m_Expression.GetBuffer());
	const char* expr = s.GetBuffer();
	const char* rest = expr;
	while (1) {
		cparser::calculator::calculate(rest, vars, ";", &rest);
		if (*rest == '\0')
			break;
	}
	return true;
}
