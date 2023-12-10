// реализация пользовательского приложения
#include "arithmetic.h"
int main()
{
	while (true) {
	try {
			std::string str;
			std::cout << "Enter a string what you want to count or enter \"end\" to end work with program: \n";
			std::cin >> str;
			if (str == "end") break;
			system("cls");
			TPostfix solution(str);
			std::cout << str << '\n' << "Res: " << solution.count() << '\n';
	}
	catch (std::exception& e) {
		std::cout << e.what() << '\n';
	}
	}
}
