// реализация пользовательского приложения
#include "arithmetic.h"
int main()
{
	while (true) {
	try {
			std::string str;
			std::cout << "Enter a string what you want to count or enter \"end\" to end work with program \n";
			std::cout << "Availble math fuctions:sin, cos, tan, cot, exp, log \n";
			std::cout << "After functions you need to enter \'(\', notation like \"a+-b\" is not available (only \"a+(-b)\")\n";
			std::cout << "You can enter an unlimited number of variables. Available variable names: x, x#any set of numbers#\n";
			std::cin >> str;
			if (str == "end") break;
			TPostfix solution(str);
			system("cls");
			std::cout << str << '\n';
			std::cout << "Res: " << solution.count() << "\n\n";
	}
	catch (std::exception& e) {
		std::cout << e.what() << '\n';
	}
	}
}
