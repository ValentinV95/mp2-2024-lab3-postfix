// реализация пользовательского приложения
#include "arithmetic.h"
#include <iomanip>



int main()
{
	try {
		std::cout << "type \'exit\' for exit\ntype expression for calculation:\n";
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
			//e.print_rpn();
			//std::cout << "\n";
			std::cout << std::setprecision(15) << e.simple_calc();
			std::cout << "\n";

		}
	}
	catch (std::exception& e) { std::cout << e.what() << std::endl; exit(-1); };
}
