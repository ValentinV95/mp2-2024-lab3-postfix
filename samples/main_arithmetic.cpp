// реализация пользовательского приложения
#include "parse_digits.h"
#include "parse_string.h"
#include "arithmetic.h"
#include <iostream>
#include <iomanip>

int main()
{
	
	while (true) {

		std::string s;
		
		getline(std::cin, s);
		if (s == "exit") {
			break;
		}
		TArithmeticExpression e(s);
		e.print_infix();
		e.ToPostfix();
		e.print_rpn();
		std::cout << e.simple_calc();
		std::cout << "\n";
		
	}
	
}
