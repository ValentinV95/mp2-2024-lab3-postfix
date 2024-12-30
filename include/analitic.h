#pragma once
#include "lexem.h"
#include "simple_math.h"

class AnaliticExpression
{
private:
	string infix;
	Vec<lexem*> postfix;
	void ToPostfix();
public:
	AnaliticExpression();
	AnaliticExpression(string const& s);
	ostream& PrintInfix(ostream& ostr) const;
	ostream& PrintPostfix(ostream& ostr) const;
};