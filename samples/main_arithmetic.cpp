// реализация пользовательского приложения
#include "arithmetic.h"
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
		std::cout << "\n";
		e.ToPostfix();
		e.print_rpn();
		std::cout << "\n";
		std::cout << e.simple_calc();
		std::cout << "\n";
		
	}
	
}
