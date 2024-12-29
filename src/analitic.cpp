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
	return;
}

ostream& AnaliticExpression::PrintInfix(ostream& ostr) const
{
	ostr << infix;
	return ostr;
}

ostream& AnaliticExpression::PrintPostfix(ostream& ostr) const
{
	if (!postfix[0])
	{
		ostr << *postfix[0];
		size_t sz = postfix.GetSize();
		for (size_t i = 1; i < sz; i++)
			ostr << " " << *postfix[i];
	}
	return ostr;
}