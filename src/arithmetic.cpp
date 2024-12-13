#include "arithmetic.h"

TArithmeticExpression::TArithmeticExpression(const std::string& s) {
	expression = s;
	infix_form = Main_Parser(s);
}