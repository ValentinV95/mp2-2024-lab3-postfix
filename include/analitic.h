#pragma once
#include "lexem.h"

class AnaliticExpression
{
private:
	string infix;
	Vec<lexem*> postfix;
	void ToPostfix();
public:
	AnaliticExpression();
	AnaliticExpression(string const& s);
};