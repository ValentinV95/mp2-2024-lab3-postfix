#include "arithmetic.h"
#include "parsers.h"

ArithmeticExpression::ArithmeticExpression() : postfix(1)
{
	infix = string();
	postfix.push_back(nullptr);
}

ArithmeticExpression::ArithmeticExpression(string const& s)
{
	infix = PreParse(s);
	ToPostfix();
}

void ArithmeticExpression::ToPostfix()
{
	postfix = MainParse(infix);
	return;
}

ostream& ArithmeticExpression::PrintInfix(ostream& ostr) const
{
	ostr << infix;
	return ostr;
}

ostream& ArithmeticExpression::PrintPostfix(ostream& ostr) const
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