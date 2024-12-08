#include <iostream>
#include "arithmetic.h"
#include "inputException.h"
#include "Vector.h"

int main()
{
	std::cout << "rules: " << std::endl;
	std::cout << "1. The variables are named 'x' + a non-negative constant. For example, just 'x', 'x1' or 'x3244'." << std::endl;
	std::cout << "2. Several unary cons need to be framed with parentheses. For example, '-(-6)'." << std::endl;
	std::cout << "3. The calculator supports the following mathematical functions:" << std::endl;
	std::cout << "   sin(x)" << std::endl;
	std::cout << "   cos(x)" << std::endl;
	std::cout << "   sqrt(x)" << std::endl;
	std::cout << "   ln(x)" << std::endl;
	std::cout << "   log2(x)" << std::endl;
	std::cout << "4. The argument of functions is always enclosed in parentheses." << std::endl;
	std::cout << "Enter an arithmetic expression:" << std::endl;
	std::string expression;
	std::getline(std::cin, expression);
	Vector<lexem*> lx, postfixLx;
	try
	{
		lx = parsingLexem(expression);
		inputVar(lx);
		postfixLx = toPostfix(lx);
		std::cout << calcArithmetic(postfixLx);
	}
	catch (const inputException& ex)
	{
		std::cout << expression << std::endl;
		if (ex.getPosLexemException() != -1)
		{
			for (int i = 0; i < ex.getPosLexemException(); i++) std::cout << " ";
			std::cout << "^" << std::endl;
		}
		std::cout << ex.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "incorrect input" << std::endl;
	}
	deleteLx(lx);
	deleteLx(postfixLx);
	return 0;
}