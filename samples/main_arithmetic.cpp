#include <iostream>
#include <exception>
#include "arithmetic.h"
#include "inputException.h"
#include "Vector.h"

void printLx(Vector<lexem*> lx)
{
	for (int i = 0; i < lx.length(); i++)
	{
		if (lx[i]->what() == 0)
		{
			std::cout << (dynamic_cast<operand*>(lx[i]))->getValue() << " " << lx[i]->getInitPos() << std::endl;
		}
		if (lx[i]->what() == 1)
		{
			std::cout << (dynamic_cast<operation*>(lx[i]))->getOperation() << " " << lx[i]->getInitPos() << std::endl;
		}
	}
	std::cout << std::endl;
}

bool checkVarible(Vector<lexem*> lx) noexcept
{
	for (int i = 0; i < lx.length(); i++)
	{
		if (lx[i]->what() == -1)
		{
			return true;
		}
	}
	return false;
}

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
		if (checkVarible(lx))
		{
			bool calc = true;
			do
			{
				Vector<lexem*> tlx;
				for (int i = 0; i < lx.length(); i++)
				{
					if (lx[i]->what() == 0)
					{
						tlx.push_back(new operand((dynamic_cast<operand*>(lx[i]))->getValue(), lx[i]->getInitPos()));
					}
					if (lx[i]->what() == 1)
					{
						tlx.push_back(new operation((dynamic_cast<operation*>(lx[i]))->getOperation(), lx[i]->getInitPos()));
					}
					if (lx[i]->what() == -1)
					{
						tlx.push_back(new varible((dynamic_cast<varible*>(lx[i]))->getName(), lx[i]->getInitPos()));
					}
				}
				inputVar(tlx);
				postfixLx = toPostfix(tlx);
				std::cout << calcArithmetic(postfixLx) << std::endl;
				std::cout << "Should new variable values be introduced: Yes(1) No(0) " << std::endl;
				int ans;
				std::cin >> ans;
				if (ans == 0) calc = false;
				else if (ans != 1)
				{
					throw std::exception("incorrect answer");
				}
				deleteLx(tlx);
				deleteLx(postfixLx);
			} while (calc);
		}
		else
		{
			inputVar(lx);
			postfixLx = toPostfix(lx);
			//printLx(postfixLx);
			std::cout << calcArithmetic(postfixLx);
			deleteLx(postfixLx);
		}
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
	
	return 0;
}