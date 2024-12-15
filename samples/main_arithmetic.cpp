// реализация пользовательского приложения
#include "arithmetic.h"
#include <iomanip>



int main()
{
	std::cout << "User's manual in directory mp2-2024-lab3-postfix. Please read it before use.\n";
	
	try {
		
		while (true) {
			std::cout << "----------------------------------------------------------\n";
			std::cout << "type \'!exit\' for exit\ntype expression for calculation:\n";
			std::string s;

			getline(std::cin, s);
			if (s == "!exit") {
				break;
			}
			TArithmeticExpression e(s);
			//e.print_infix();
			//std::cout << "\n";
			e.ToPostfix();
			//e.print_rpn();
			//std::cout << "\n";
			std::cout << std::setprecision(15) << e.simple_calc();
			std::cout << "\n";

		}
	}
	catch (std::exception& e) { std::cout << e.what() << std::endl; exit(-1); };
}
