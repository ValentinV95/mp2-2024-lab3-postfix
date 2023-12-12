// реализация пользовательского приложения
#include "arithmetic.h"
int main()
{
	std::string str;
	while (true) {
	try {
			int fl = 0;
			std::cout << "Enter a string what you want to count or enter \"end\" to end work with program \n";
			std::cout << "Availble math fuctions:sin, cos, tan, cot, exp, log \n";
			std::cout << "After functions you need to enter \'(\'\n";
			std::cout << "You can enter an unlimited number of variables. Available variable names: x, x#any set of numbers#\n";
			std::getline(std::cin, str);
			if (str == "end") break;
			if (str == "") {
				system("cls");
				continue;
			}
			for (int i = 0; i < str.size(); i++) if (str[i] == 'x') fl = 1;
			TPostfix solution(str);
			system("cls");
			do {
				std::cout << str << '\n';
				std::cout << "Res: " << solution.count() << "\n\n";
				if (fl) {
					do {
						std::cout << "Enter \'1\' if you want to recalculate an expression with new variables or enter \'0\' to enter new expression: ";
						std::cin >> fl;
						if (fl != 0 && fl != 1) std::cout << "This option does not exist\n";
					} while (fl != 0 && fl != 1);
					system("cls");
				}
			}
			while (fl);
	}
	catch (std::exception& e) {
		system("cls");
		std::cout << str << '\n';
		std::cout << e.what() << "\n\n";
	}
	}
}
