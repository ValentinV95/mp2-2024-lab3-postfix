#include "analitic.h"
#include "parsers.h"

AnaliticExpression::AnaliticExpression() : postfix(1)
{
	infix = string();
	postfix.push_back(nullptr);
}

AnaliticExpression::AnaliticExpression(string const& s)
{
	infix = PreParse(s);
	ToPostfix();
}

void AnaliticExpression::ToPostfix()
{
	postfix = MainParse(infix);
}