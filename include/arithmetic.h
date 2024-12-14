#pragma once
#include "parse_string.h"
#include "stack.h"
#define _is_func(a) (a==-3 || a==3 || a==-4 || a==4)

class TArithmeticExpression {
	
	vector<lexem*> infix_form;
	vector<lexem*> postfix_form;
	std::string expression;

public:

	TArithmeticExpression(const std::string&);
	void print_rpn();
	void print_infix();

	void ToPostfix();
	double simple_calc();
};