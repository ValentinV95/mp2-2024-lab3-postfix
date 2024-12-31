#pragma once
#include "lexem.h"
#include "simple_math.h"

class ArithmeticExpression
{
private:
	string infix;
	Vec<lexem*> postfix;
	void ToPostfix();
public:
	ArithmeticExpression();
	ArithmeticExpression(string const& s);
	ostream& PrintInfix(ostream& ostr) const;
	ostream& PrintPostfix(ostream& ostr) const;
};